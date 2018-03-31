// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BattleTank.h"




ATank* ATankPlayerController::GetControlledTank() const
{
    auto tank = Cast<ATank>(GetPawn());
    return tank;
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ATank* controlledTank = GetControlledTank())
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller is controlling %s"), *(controlledTank->GetName()))
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
    //UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *screenLocation.ToString());
    return screenLocation;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
    FVector2D screenLocation = GetScreenLocation();
    FVector worldLocation;
    FVector worldDirection;
    if (GetLookDirection(screenLocation, worldLocation, worldDirection))
    {
        if (this->GetLookVectorHitLocation(worldLocation, worldDirection, hitLocation))
        {
            UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *hitLocation.ToString());
        }
    }

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector &worldLocation, FVector &worldDirection) const
{
    if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, worldDirection))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s, World Location: %s, World Direction: %s"), *screenLocation.ToString(), *worldLocation.ToString(), *worldDirection.ToString());
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

    if (AActor* hitActor = hit.GetActor())
    {
        UE_LOG(LogTemp, Warning, TEXT("The struck actor is %s"), *(hitActor->GetName()));
        hitLocation = hit.Location;
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Actor struck"));
    }

    return false;
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (ATank* controlledTank = GetControlledTank())
    {
        FVector hitLocation;
        
        if (GetSightRayHitLocation(hitLocation))
        {
            //UE_LOG(LogTemp, Warning, TEXT("Hit location is %s"), *hitLocation.ToString());

        }
    }
}
