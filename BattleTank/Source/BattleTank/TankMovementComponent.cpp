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
void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto owner = GetOwner();
	UE_LOG(LogTemp, Warning, TEXT("%s request direct move of  %s"), *owner->GetName(), *MoveVelocity.ToString());
}

void UTankMovementComponent::IntendMoveForward(float throwForward)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(throwForward);
		RightTrack->SetThrottle(throwForward);
	}
}

void UTankMovementComponent::IntendMoveRight(float movement)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(movement);
		RightTrack->SetThrottle(-movement);
	}
}
