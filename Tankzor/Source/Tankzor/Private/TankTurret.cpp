// Fill out your copyright notice in the Description page of Project Settings.

#include "Tankzor.h"
#include "TankTurret.h"



void UTankTurret::Rotate(float RelativeSpeed) {
	// Move the barrel the right amount this frame
	// Given a max elevation and the frame time

	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	auto RotationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));

}
