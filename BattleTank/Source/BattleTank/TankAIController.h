// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:

    void Tick(float DeltaTime) override;
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    APawn* GetPlayerTank() const;

	float AcceptanceRadius = 3000;
	
};
