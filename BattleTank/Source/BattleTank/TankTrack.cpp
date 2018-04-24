// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
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