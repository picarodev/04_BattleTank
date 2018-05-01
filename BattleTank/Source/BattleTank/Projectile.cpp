// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"



// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(false);

    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    ImpactBlast->bAutoActivate = false;

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    ProjectileMovementComponent->bAutoActivate = false;

    ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
    ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    FScriptDelegate del;
    del.BindUFunction(this, "OnHit");
    OnActorHit.AddUnique(del);

}

void AProjectile::OnHitTimerExpiration()
{
    this->Destroy();
}

void AProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    LaunchBlast->Deactivate();
    ImpactBlast->Activate();
    ExplosionForce->FireImpulse();

    SetRootComponent(ImpactBlast);
    CollisionMesh->DestroyComponent();

    
    FTimerHandle timerHandle;
    GetWorld()->GetTimerManager().SetTimer(timerHandle,
        this,
        &AProjectile::OnHitTimerExpiration,
        DestructionDelay);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	ProjectileMovementComponent->Activate();
}