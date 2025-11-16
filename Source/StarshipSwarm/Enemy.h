// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemyKilledEvent);


UCLASS()
class STARSHIPSWARM_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
    float Health = 50.f;

    // Amount of score the player gets for killing this enemy (optional)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
    int32 ScoreValue = 100;

    // Called by bullets or other damaging things
    UFUNCTION(BlueprintCallable, Category="Enemy")
    void ApplyDamage(float DamageAmount);
    if (Health <= 0.f)
    {
        OnEnemyKilled.Broadcast();
        OnDeath();
        Destroy();
    }

    
    UPROPERTY(BlueprintAssignable, Category="Enemy")
    FEnemyKilledEvent OnEnemyKilled;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UFUNCTION(BlueprintImplementableEvent, Category="Enemy")
    void OnDamaged();
    
    UFUNCTION(BlueprintImplementableEvent, Category="Enemy")
    void OnDeath();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
