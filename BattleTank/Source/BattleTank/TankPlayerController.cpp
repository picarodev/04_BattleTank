// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"




ATank* ATankPlayerController::GetControlledTank() const
{
    auto possessedPawn = Cast<ATank>(GetPawn());
    return nullptr;
}