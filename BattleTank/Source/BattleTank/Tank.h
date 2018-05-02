// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDestroyed);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
    float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const;

    FTankDestroyed OnTankDestroyed;

protected:
    void BeginPlay() override;


private:
	// Sets default values for this pawn's properties
	ATank();

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 100.0;

    UPROPERTY(VisibleAnywhere, Category = "Health")
    int32 CurrentHealth = 0;
    
};
