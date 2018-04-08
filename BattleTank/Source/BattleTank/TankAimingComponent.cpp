// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
    Barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet)
{
    Turret = turretToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UStaticMeshComponent* UTankAimingComponent::GetTurret() const
{
    if (Barrel)
    {
        TArray<USceneComponent*> parents;
        Barrel->GetParentComponents(parents);
        return Cast<UStaticMeshComponent>(parents[0]);
    }

    return nullptr;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
    FRotator aimAsRotator = aimDirection.Rotation();

    FRotator turretRotator = Turret->GetForwardVector().Rotation();
    auto turretDelta = aimAsRotator - turretRotator;

    FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
    auto barrelDelta = aimAsRotator - barrelRotator;

    Turret->Rotate(barrelDelta.Yaw);
    Barrel->Elevate(barrelDelta.Pitch);
}

void UTankAimingComponent::AimAt(FVector hitLocation, float LaunchSpeed)
{
    if (Barrel)
    {
        UWorld* world = GetWorld();
        FVector tossVelocity;
        FVector start = Barrel->GetSocketLocation(FName("NozelSocket"));
        FVector end = hitLocation;
        float speed = LaunchSpeed;
        FCollisionResponseParams responseParams;
        TArray<AActor*> actorsToIgnore;

        float timeSeconds = GetWorld()->GetTimeSeconds();
        if (UGameplayStatics::SuggestProjectileVelocity(world, tossVelocity, start, end, speed, false,
            0.0f, 0.0f, ESuggestProjVelocityTraceOption::Type::DoNotTrace, responseParams, actorsToIgnore, false))
        {
            FVector tossNormalized = tossVelocity.GetSafeNormal();
            //UE_LOG(LogTemp, Warning, TEXT("%f: Fire direction %s"), timeSeconds, *tossNormalized.ToString());
            MoveBarrelTowards(tossNormalized);
        }
        else
        {
            //UE_LOG(LogTemp, Warning, TEXT("%f: No Solution Found"), timeSeconds);
        }
    }
}
