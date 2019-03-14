// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;


/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKZOR_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);


private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
	
};
