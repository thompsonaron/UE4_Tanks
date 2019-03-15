// Fill out your copyright notice in the Description page of Project Settings.

#include "Tankzor.h"
#include "Tank.h"
#include "TankAIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}



void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (PlayerTank)
	{
		//  move towards the player
		//			to whom, distance from target max in cm, 
		MoveToActor(PlayerTank, 3000);

		//aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// fire if rdy
		ControlledTank->FireProjectile(); // TODO limit fire rate
		
	}
}
