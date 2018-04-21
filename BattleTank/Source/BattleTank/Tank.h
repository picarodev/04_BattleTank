// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankBarrel;
class UTankTurret;
class AProjectile;

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void Fire();

private:	
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
    double ReloadTimeInSeconds = 3.0;

	double LastFireTime = -1e6;

	UTankBarrel* Barrel = nullptr;
};
