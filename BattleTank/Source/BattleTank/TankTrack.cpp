// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

// (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
// (AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
void UTankTrack::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("HITTTTTTT!!!!!!!!!!!!!"));  // TODO
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	FScriptDelegate del;
	del.BindUFunction(this, "OnHit");
	OnComponentHit.AddUnique(del);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto correctingAcceleration = -(slippageSpeed / DeltaTime) * GetRightVector();

	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	float numberOfTracks = 2.0;
	auto correctionForce = tankRoot->GetMass() * correctingAcceleration * (1.0 / numberOfTracks);

	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
	auto name = GetName();
	auto forceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}