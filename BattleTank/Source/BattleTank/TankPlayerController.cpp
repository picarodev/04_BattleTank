// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
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

}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (ATank* controlledTank = GetControlledTank())
    {

    }
}
