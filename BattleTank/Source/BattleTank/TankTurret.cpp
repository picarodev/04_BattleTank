// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"




void UTankTurret::Rotate(float relativeSpeed)
{
    relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.0f, 1.0f);
    auto rotationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto rawNewRotation = RelativeRotation.Yaw + rotationChange;
    SetRelativeRotation(FRotator(0.0f, rawNewRotation, 0.0f));
}