// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankBarrel;
class UTankTurret;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    void SetBarrelReference(UTankBarrel* barrelToSet);

    void SetTurretReference(UTankTurret* barrelToSet);

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void AimAt(FVector hitLocation, float LaunchSpeed);

    // Called when the game starts
    virtual void BeginPlay() override;

private:	
    UStaticMeshComponent* GetTurret() const;

    void MoveBarrelTowards(FVector aimDirection);

    UTankBarrel* Barrel = nullptr;
		
    UTankTurret* Turret = nullptr;

};
