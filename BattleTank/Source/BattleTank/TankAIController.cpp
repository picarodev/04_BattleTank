// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "BattleTank.h"


void ATankAIController::OnTankDestroyed()
{
    UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller notified of tank destruction"));
    
    if (GetPawn())
    {
        GetPawn()->DetachFromControllerPendingDestroy();
    }
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        auto possessedTank = Cast<ATank>(InPawn);

        if (possessedTank)
        {
            FScriptDelegate del;
            del.BindUFunction(this, "OnTankDestroyed");
            possessedTank->OnTankDestroyed.AddUnique(del);
        }
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	UTankAimingComponent* aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(aimingComponent))
	{
		auto playerTank = GetPlayerTank();
		if (playerTank)
        {
			MoveToActor(playerTank, AcceptanceRadius);
			aimingComponent->AimAt(playerTank->GetActorLocation());

            if (aimingComponent->GetFiringState() == EFiringStatus::Locked)
            {
                aimingComponent->Fire();
            }
        }
    }
}

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
	auto controlledTank = GetPawn();
    if (ensure(controlledTank))
    {
		auto playerTank = GetPlayerTank();
        if (ensure(playerTank))
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

APawn* ATankAIController::GetPlayerTank() const
{
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
    if (ensure(controller))
    {
		APawn* pawn = controller->GetPawn();
		return pawn;
    }

    return nullptr;
}
