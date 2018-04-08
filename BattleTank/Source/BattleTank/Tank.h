// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankAimingComponent;
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

    void AimAt(FVector hitLocation);

    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetBarrelReference(UTankBarrel* barrelToSet);

    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetTurretReference(UTankTurret* turretToSet);

    UFUNCTION(BlueprintCallable, Category = Actions)
    void Fire();

protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

private:	
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 3000;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	double ReloadTimeInSeconds = 3.0;

	double LastFireTime = -1e6;

	UTankBarrel* Barrel = nullptr;
};
