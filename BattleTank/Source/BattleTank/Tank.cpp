// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming component"));
}

void ATank::AimAt(FVector hitLocation)
{
    TankAimingComponent->AimAt(hitLocation, LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	if (!ProjectileBlueprint)
	{
		UE_LOG(LogTemp, Error, TEXT("No projectile blueprint set in Tank blueprint, using default"));
	}
}

void ATank::SetBarrelReference(UTankBarrel * barrelToSet)
{
    TankAimingComponent->SetBarrelReference( barrelToSet );
	Barrel = barrelToSet;
}

void ATank::SetTurretReference(UTankTurret * turretToSet)
{
    TankAimingComponent->SetTurretReference(turretToSet);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded)
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
		UE_LOG(LogTemp, Warning, TEXT("Projectile blueprint is %s"), *ProjectileBlueprint->GetName());
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Failed to fire."));
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

