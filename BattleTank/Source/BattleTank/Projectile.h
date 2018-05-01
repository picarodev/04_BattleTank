// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

    UFUNCTION(BlueprintCallable)
    void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* CollisionMesh = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* LaunchBlast = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* ImpactBlast = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    URadialForceComponent* ExplosionForce = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float DestructionDelay = 20.0;

    void OnHitTimerExpiration();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float speed);

	
	
};
