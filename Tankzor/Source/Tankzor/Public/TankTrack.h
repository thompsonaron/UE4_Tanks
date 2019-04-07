// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *TankTrack  is used to set maximum driving foce and to apply forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKZOR_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UTankTrack();

	// Sets throttle between +1 and -1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	void DriveTrack();

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; // assume 40 tonne tank and 1g acceleration

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void ApplySidewaysForce();

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	float CurrentThrottle = 0;
};
