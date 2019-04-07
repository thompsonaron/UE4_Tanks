// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class TANKZOR_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

protected:
	// how close can the AI tank get to target (in cm)
	UPROPERTY(EditDefaultsOnly, Category = "Setup") // TODO consider EditDefaultsOnly
	float AcceptanceRadius = 8000;
};
