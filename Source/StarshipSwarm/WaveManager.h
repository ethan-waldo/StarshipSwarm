#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FormationManager.h"
#include "WaveManager.generated.h"

UCLASS()
class STARSHIPSWARM_API AWaveManager : public AActor
{
    GENERATED_BODY()
    
public:
    AWaveManager();

protected:
    virtual void BeginPlay() override;

public:
    // List of formation blueprints to spawn as each wave
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Waves")
    TArray<TSubclassOf<AFormationManager>> WaveFormations;

    // Index of current wave
    int32 CurrentWaveIndex = -1;

    // Spawns the next wave
    void SpawnNextWave();

    // Called by FormationManager when all enemies die
    UFUNCTION()
    void OnWaveCleared();
};
