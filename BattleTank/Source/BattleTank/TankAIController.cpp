// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "BattleTank.h"



ATank* ATankAIController::GetControlledTank() const
{
    auto tank = Cast<ATank>(GetPawn());
    return tank;
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (ATank* controlledTank = GetControlledTank())
    {
        if (ATank* playerTank = GetPlayerTank())
        {
            controlledTank->AimAt(playerTank->GetActorLocation());
        }
    }
}

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    if (ATank* controlledTank = GetControlledTank())
    {
        if (ATank* playerTank = GetPlayerTank())
        {
            UE_LOG(LogTemp, Warning, TEXT("AI Controller controlling %s says that the player tank is %s"), *(controlledTank->GetName()), *(playerTank->GetName()))
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("AI Controller controlling %s couldn't find player tank"), *(controlledTank->GetName()))
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI controller says it is not controlling a tank"))
    }
}

ATank* ATankAIController::GetPlayerTank() const
{
    if (APlayerController* controller = GetWorld()->GetFirstPlayerController())
    {
        if (APawn* pawn = controller->GetPawn())
        {
            return Cast<ATank>(pawn);
        }
    }

    return nullptr;
}
