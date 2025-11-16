#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "FormationManager.generated.h"

// Delegate for notifying when all enemies in the formation are dead
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFormationCleared);


int32 AliveEnemies = 0;

UFUNCTION()
void OnEnemyDestroyed(AActor* DestroyedActor);

void AdvanceToNextWave();


UCLASS()
class STARSHIPSWARM_API AFormationManager : public AActor
{
    GENERATED_BODY()
    
public:
    AFormationManager();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RowSpacing = 200.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EnemySpacing = 150.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FEnemyRowSettings> RowSettings;

    // Let WaveManager bind to this
    UPROPERTY(BlueprintAssignable, Category="Formation")
    FOnFormationCleared OnFormationCleared;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 CurrentWaveIndex = 0;
    int32 AliveEnemies = 0;
    
    UFUNCTION()
    void OnEnemyDestroyed(AActor* DestroyedActor);

    void AdvanceToNextWave();

private:
    FVector InitialLocation;
    float Time = 0.0f;

    // Track enemies currently alive in this formation
    int32 AliveEnemies = 0;

    // Called whenever an enemy dies
    UFUNCTION()
    void HandleEnemyDeath();
};
