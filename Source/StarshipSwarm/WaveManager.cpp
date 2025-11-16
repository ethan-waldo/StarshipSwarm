#include "WaveManager.h"
#include "Kismet/GameplayStatics.h"

AWaveManager::AWaveManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AWaveManager::BeginPlay()
{
    Super::BeginPlay();
    SpawnNextWave();
}

void AWaveManager::SpawnNextWave()
{
    CurrentWaveIndex++;

    if (WaveFormations.IsValidIndex(CurrentWaveIndex))
    {
        // Spawn wave at WaveManager's location
        AFormationManager* Formation = GetWorld()->SpawnActor<AFormationManager>(
            WaveFormations[CurrentWaveIndex],
            GetActorTransform()
        );

        // Register callback for when formation is cleared
        Formation->OnFormationCleared.AddDynamic(this, &AWaveManager::OnWaveCleared);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ALL WAVES COMPLETED!"));
        // You can trigger "You win!" UI or boss wave here
    }
}

void AWaveManager::OnWaveCleared()
{
    SpawnNextWave();
}
