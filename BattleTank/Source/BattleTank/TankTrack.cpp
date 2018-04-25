// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
// (AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
void UTankTrack::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.0f;
}

UTankTrack::UTankTrack()
{
	FScriptDelegate del;
	del.BindUFunction(this, "OnHit");
	OnComponentHit.AddUnique(del);
}

void UTankTrack::ApplySidewaysForce()
{
	float DeltaTime = this->GetWorld()->GetDeltaSeconds();
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto correctingAcceleration = -(slippageSpeed / DeltaTime) * GetRightVector();
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	float numberOfTracks = 2.0;
	auto correctionForce = tankRoot->GetMass() * correctingAcceleration * (1.0 / numberOfTracks);
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + throttle, -1.0f, 1.0f);
}

void UTankTrack::DriveTrack()
{
	auto forceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}