// Fill out your copyright notice in the Description page of Project Settings.

#include "Tankzor.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
// Depends on movement component via pathfinding system



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AIAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (!ensure(PlayerTank && AIAimingComponent)) { return; }
	//  move towards the player(to whom, distance from target max in cm)
	MoveToActor(PlayerTank, 3000);
	//aim towards the player
	AIAimingComponent->AimAt(PlayerTank->GetActorLocation());
	
	
	// fire if rdy
	AIAimingComponent->FireProjectile(); // TODO limit fire rate
}
