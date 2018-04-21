// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"




void UTankTrack::SetThrottle(float throttle)
{
	auto name = GetName();
	auto forceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}