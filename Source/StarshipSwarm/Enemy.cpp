// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::ApplyDamage(float DamageAmount)
{
    Health -= DamageAmount;

    // Let BP react to getting hit (flash, sound, etc.)
    OnDamaged();

    if (Health <= 0.f)
    {
        // Blueprint hook for explosion, score UI, etc.
        OnDeath();

        // Actually remove the enemy
        Destroy();
    }
}

