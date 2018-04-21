// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("ATank::ATank() called for %s"), *(this->GetName()))

}

void ATank::AimAt(FVector hitLocation)
{
	if (TankAimingComponent)
	{
		TankAimingComponent->AimAt(hitLocation, LaunchSpeed);
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Tank::BeginPlay: Inside beginplay..."));  // TODO

	if (!ProjectileBlueprint)
	{
		UE_LOG(LogTemp, Warning, TEXT("No projectile blueprint set in Tank blueprint, using default"));  // TODO
	}
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded && ProjectileBlueprint)
	{
		UWorld* world = GetWorld();
		auto projectile = world->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("NozelSocket")),
			Barrel->GetSocketRotation(FName("NozelSocket"))
			);

		if (projectile)
		{
			projectile->LaunchProjectile(LaunchSpeed);
		}

		LastFireTime = FPlatformTime::Seconds();
	}
	else
	{
	}
}

