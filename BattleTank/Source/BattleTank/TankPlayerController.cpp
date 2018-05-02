// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"
#include "BattleTank.h"



void ATankPlayerController::OnTankDestroyed()
{
    UE_LOG(LogTemp, Warning, TEXT("Player Tank Controller notified of tank destruction"));
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        auto possessedTank = Cast<ATank>(InPawn);

        if (ensure(possessedTank))
        {
            FScriptDelegate del;
            del.BindUFunction(this, "OnTankDestroyed");
            possessedTank->OnTankDestroyed.AddUnique(del);
        }
    }
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
	APawn* controlledTank = GetPawn();

    if (ensure(controlledTank))
    {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller is controlling %s"), *(controlledTank->GetName()));
		UTankAimingComponent* aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
		if (ensure(aimingComponent))
		{
			FoundAimingComponent(aimingComponent);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s has no aiming component"), *controlledTank->GetName());
		}
	}
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player controller is not controlling a tank"))
    }

}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair();
}

FVector2D ATankPlayerController::GetScreenLocation() const
{
    int32 viewportSizeX, viewportSizeY;
    GetViewportSize(viewportSizeX, viewportSizeY);
    FVector2D screenLocation = FVector2D(viewportSizeX * CrossHairXLocation, viewportSizeY * CrossHairYLocation);
    return screenLocation;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
    FVector2D screenLocation = GetScreenLocation();
    FVector worldLocation;
    FVector worldDirection;
	if (GetLookDirection(screenLocation, worldLocation, worldDirection))
	{
		return GetLookVectorHitLocation(worldLocation, worldDirection, hitLocation);
	}

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector &worldLocation, FVector &worldDirection) const
{
    if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, worldDirection))
    {
        return true;
    }

    return false;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector worldLocation, FVector worldDirection, FVector& hitLocation) const
{
    FHitResult hit;
    FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());
    ECollisionChannel channel = ECollisionChannel::ECC_Visibility;
    FVector end = worldLocation + worldDirection * LineTraceRange;
    GetWorld()->LineTraceSingleByChannel(
        OUT hit,
        worldLocation,
        end,
        channel,
        traceParameters
    );

	AActor* hitActor = hit.GetActor();
    if (hitActor)
    {
        hitLocation = hit.Location;
        return true;
    }

    return false;
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetPawn())
	{
		UTankAimingComponent* aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (ensure(aimingComponent))
		{
			FVector hitLocation;

			if (GetSightRayHitLocation(hitLocation))
			{
				aimingComponent->AimAt(hitLocation);
			}
		}
	}
}
