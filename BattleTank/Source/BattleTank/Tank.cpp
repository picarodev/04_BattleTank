// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


float ATank::GetHealthPercent() const
{
    return (float)CurrentHealth / (float)StartingHealth;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

float ATank::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    int32 damagePoints = FPlatformMath::RoundToInt(Damage);
    int32 damageToApply = FMath::Clamp<int32>(Damage, 0, CurrentHealth);
    CurrentHealth -= damageToApply;

    if (CurrentHealth <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank destroyed!!!"));
    }
    return damageToApply;
}