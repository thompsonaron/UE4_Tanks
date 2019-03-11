// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;
/**
 * 
 */
UCLASS()
class TANKZOR_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATankPlayerController();

	ATank* GetControlledTank() const;

	void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;


	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsReticle();


private:
	// return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation= 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0;

	bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
