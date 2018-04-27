// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
    OutOfAmmo,
};

class UTankBarrel;
class UTankTurret;
class AProjectile;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* barrel, UTankTurret* turret);

	

    // Called every frame
    void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void AimAt(FVector hitLocation);

    // Called when the game starts
    virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void Fire();

    EFiringStatus GetFiringState() const;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 6000;


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int AmmoCount = 5;


private:
	bool IsReloaded() const;
	bool IsBarrelMoving() const;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	double ReloadTimeInSeconds = 3.0;

	double LastFireTime = -1e6;

    UStaticMeshComponent* GetTurret() const;

    void MoveBarrelTowards();

    UTankBarrel* Barrel = nullptr;
		
    UTankTurret* Turret = nullptr;

	FVector AimDirection;

};
