// Fill out your copyright notice in the Description page of Project Settings.

#include "Tankzor.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {
	//auto WorldTime = GetWorld()->GetTimeSeconds();

	auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);

	// TODO clamp actual throttle value so player can't over-drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	//auto TankRoot = 
}
