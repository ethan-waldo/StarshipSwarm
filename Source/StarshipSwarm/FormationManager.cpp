// Fill out your copyright notice in the Description page of Project Settings.


#include "FormationManager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values
AFormationManager::AFormationManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AFormationManager::BeginPlay()
{
    Super::BeginPlay();
    
    const FVector Origin = GetActorLocation();
    
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
        
        // Loop through enemies in row
        for (int32 ColIndex = 0; ColIndex < Count; ColIndex++)
        {
            float X = RowIndex * RowSpacing;
            float Y = (ColIndex * EnemySpacing) - CenterOffset;
            
            FVector SpawnLocation = Origin + FVector(X, Y, 0);
            FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation);
            
            GetWorld()->SpawnActor<AActor>(Settings.EnemyClass, SpawnTransform);
        }
    }
}



