// Fill out your copyright notice in the Description page of Project Settings.

#include "MortarBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"




//void UMortarBarrel::Elevate(float relativeSpeed)
//{
//    relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.0f, 1.0f);
//    auto elevationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
//    auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
//    rawNewElevation = FMath::Clamp<float>(rawNewElevation, MinElevationDegrees, MaxElevationDegrees);
//    SetRelativeRotation(FRotator(rawNewElevation, 0.0f, 0.0f));
//}