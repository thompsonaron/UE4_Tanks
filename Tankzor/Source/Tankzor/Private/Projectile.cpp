// Fill out your copyright notice in the Description page of Project Settings.

#include "Tankzor.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	TankProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void AProjectile::LaunchProjectile(float Speed) 
{
	auto WorldTime = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Projectile fires at %f speed"), WorldTime, Speed);

	TankProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	TankProjectileMovementComponent->bAutoActivate = true;
}
