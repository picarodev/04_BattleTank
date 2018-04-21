// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("C++ call to ATank::ATank() (%s)"), *(this->GetName()))

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("C++ call to ATank::BeginPlay() (%s)"), *(this->GetName()))

	if (!ensure(ProjectileBlueprint))
	{
		UE_LOG(LogTemp, Warning, TEXT("No projectile blueprint set in Tank blueprint, using default"));  // TODO
	}
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (ensure(Barrel && ProjectileBlueprint))
	{
		if (isReloaded)
		{
			UWorld* world = GetWorld();
			auto projectile = world->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("NozelSocket")),
				Barrel->GetSocketRotation(FName("NozelSocket"))
				);

			if (projectile)
			{
				projectile->LaunchProjectile(1);
			}

			LastFireTime = FPlatformTime::Seconds();
		}
	}
}

