// Fill out your copyright notice in the Description page of Project Settings.

#include "Tankzor.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collison Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);


	Launch_Blast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch_Blast"));
	Launch_Blast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	

	TankProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	TankProjectileMovementComponent->bAutoActivate = false;

	

	Impact_Blast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact_Blast"));
	Impact_Blast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Impact_Blast->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void AProjectile::LaunchProjectile(float Speed) 
{
	TankProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	TankProjectileMovementComponent->bAutoActivate = true;
	TankProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit) {
	Launch_Blast->Deactivate();
	Impact_Blast->Activate(true);
}
