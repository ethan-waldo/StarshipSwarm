// Fill out your copyright notice in the Description page of Project Settings.

#include "FormationManager.h"
#include "Enemy.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values
AFormationManager::AFormationManager()
{
    // Allow this actor to tick so we can animate the formation
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFormationManager::BeginPlay()
{
    Super::BeginPlay();

    InitialLocation = GetActorLocation();
    const FVector Origin = GetActorLocation();

    AliveEnemies = 0;

    // Loop through rows
    for (int32 RowIndex = 0; RowIndex < RowSettings.Num(); RowIndex++)
    {
        const FEnemyRowSettings& Settings = RowSettings[RowIndex];

        if (!Settings.EnemyClass || Settings.EnemyCount <= 0)
        {
            continue;
        }

        const int32 Count = Settings.EnemyCount;

        // ★★★ CENTER OFFSET FORMULA ★★★
        float CenterOffset = ((Count - 1) * EnemySpacing) / 2.0f;

        // Loop through enemies in the row
        for (int32 ColIndex = 0; ColIndex < Count; ColIndex++)
        {
            float X = RowIndex * RowSpacing;
            float Y = (ColIndex * EnemySpacing) - CenterOffset;

            FVector SpawnLocation = Origin + FVector(X, Y, 0);
            FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation);

            // Spawn enemy
            AEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(Settings.EnemyClass, SpawnTransform);

            if (SpawnedEnemy)
            {
                // Count this enemy
                AliveEnemies++;

                // Bind to the enemy's death event
                SpawnedEnemy->OnEnemyKilled.AddDynamic(this, &AFormationManager::OnEnemyDestroyed);
            }
        }
    }
}

void AFormationManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Time += DeltaTime;

    // Smooth hovering motion
    float HoverX = FMath::Sin(Time * 0.5f) * 100.f;
    float HoverZ = FMath::Sin(Time * 0.8f) * 40.f;

    SetActorLocation(InitialLocation + FVector(HoverX, 0.f, HoverZ));
}

void AFormationManager::OnEnemyDestroyed(AActor* DestroyedActor)
{
    AliveEnemies--;

    UE_LOG(LogTemp, Warning, TEXT("Enemy destroyed. %d still alive"), AliveEnemies);

    if (AliveEnemies <= 0)
    {
        AdvanceToNextWave();
    }
}

void AFormationManager::AdvanceToNextWave()
{
    CurrentWaveIndex++;

    if (CurrentWaveIndex >= RowSettings.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("All waves completed!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Starting Wave %d"), CurrentWaveIndex);

    SpawnWave(RowSettings[CurrentWaveIndex]);
}


