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

    auto controlledTank = GetControlledTank();

    if (controlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play: %s"), *(controlledTank->GetName()))
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No controlled tank"))
    }
}
