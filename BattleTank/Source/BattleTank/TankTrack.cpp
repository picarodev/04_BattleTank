// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"




void UTankTrack::SetThrottle(float throttle)
{
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *name, throttle);
}