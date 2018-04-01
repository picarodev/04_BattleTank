// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
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


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * barrelToSet)
{
    Barrel = barrelToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float LaunchSpeed) const
{
    if (Barrel)
    {
        UWorld* world = GetWorld();
        const UObject* context = this->GetWorld();
        FVector tossVelocity;
        FVector start = Barrel->GetSocketLocation(FName("NozelSocket"));
        FVector end = hitLocation;
        float speed = LaunchSpeed;
        bool highArc = false;
        float collisionRadius = 0.01f;
        float overridGZ = 0.0f;
        ESuggestProjVelocityTraceOption::Type trace = ESuggestProjVelocityTraceOption::Type::DoNotTrace;
        FCollisionResponseParams responseParams;
        TArray<AActor*> actorsToIgnore;
        bool bDrawDebug = false;
        if (UGameplayStatics::SuggestProjectileVelocity(context, tossVelocity, start, end, speed, highArc,
            collisionRadius, overridGZ, trace, responseParams, actorsToIgnore, bDrawDebug))
        {
            FVector tossNormalized = tossVelocity.GetSafeNormal();
            FRotator rotation = tossNormalized.Rotation();
            Barrel->SetWorldRotation(rotation);
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Firing at %f"), LaunchSpeed);
    //UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *(GetOwner()->GetName()), *(hitLocation.ToString()), *(Barrel->GetComponentLocation().ToString()));

}
