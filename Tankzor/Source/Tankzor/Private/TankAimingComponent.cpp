// Fill out your copyright notice in the Description page of Project Settings.

#include "Tankzor.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	
	PrimaryComponentTick.bCanEverTick = true; // TODO should this tick?

	// ...


}

void UTankAimingComponent::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();


	// so that first fire is after inital reload
	LastFireTime = FPlatformTime::Seconds();

}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}


void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)){ return;	}

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileFiringSocket"));


	// Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // buggy paramater must be present

	); //Calculate the OutLaunchVelocity
	
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);	
	}	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	// Work out difference between current barrel roration and AimDirection
	auto BarrelRotator= Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
		
	Barrel->Elevate(DeltaRotator.Pitch); 
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;


	
	if (DeltaRotator.Yaw < -180)
	{
		Turret->Rotate((360 -DeltaRotator.Yaw));
	}
	else if (DeltaRotator.Yaw > 180) {
		Turret->Rotate((360 - DeltaRotator.Yaw)*-1);
	}
	else{
		Turret->Rotate(DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::FireProjectile()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	

	if (FiringState != EFiringState::Reloading) {

		// spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("ProjectileFiringSocket")),
			Barrel->GetSocketRotation(FName("ProjectileFiringSocket"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)){	return false;	}
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}