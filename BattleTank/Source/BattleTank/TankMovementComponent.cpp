// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"




void UTankMovementComponent::Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack)
{
	if (leftTrack && rightTrack)
	{
		LeftTrack = leftTrack;
		RightTrack = rightTrack;
	}
}
void UTankMovementComponent::IntendMoveForward(float throwForward)
{
	UE_LOG(LogTemp, Warning, TEXT("Intended throw forward is %f"), throwForward);
	LeftTrack->SetThrottle(throwForward);
	RightTrack->SetThrottle(throwForward);
}
