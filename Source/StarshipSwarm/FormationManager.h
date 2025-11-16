// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FormationManager.generated.h"


USTRUCT(BlueprintType)
struct FEnemyRowSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> EnemyClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 EnemyCount = 0;
};

UCLASS()
class STARSHIPSWARM_API AFormationManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFormationManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    
    virtual void Tick(float DeltaTime) override;
	// Called every frame
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RowSpacing = 200.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EnemySpacing = 150.f;

        // Array of row settings (4 rows or more)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FEnemyRowSettings> RowSettings;

private:
    FVector InitialLocation;
    
    float Time = 0.0f;

};
