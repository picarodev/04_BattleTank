// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <utility>
#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

typedef std::pair<FVector, FVector> LineBeginningAndEnd;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    ATank * GetControlledTank() const;
	
    void BeginPlay() override;

    void Tick(float DeltaTime) override;

    bool GetSightRayHitLocation(FVector & hitLocation) const;

    bool GetLookDirection(FVector2D screenLocation, FVector &worldLocation, FVector &worldDirection) const;

    bool GetLookVectorHitLocation(FVector worldLocation, FVector worldDirection, FVector& hitLocation) const;

    FVector2D GetScreenLocation() const;

    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5f;

    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.333333f;

    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000.0f;

private:
    void AimTowardsCrosshair();
};
