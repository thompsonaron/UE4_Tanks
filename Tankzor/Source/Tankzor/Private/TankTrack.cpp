// Fill out your copyright notice in the Description page of Project Settings.

#include "Tankzor.h"
#include "TankTrack.h"


UTankTrack::UTankTrack(){
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UTankTrack::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit) {
	


	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

// todo YESNO?
void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
}

void UTankTrack::ApplySidewaysForce()
{
	// calculate the slippage speed
	// work out the required acceleration this frame to correct
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// calculate and apply sideways force (F = m * a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //divided by 2 coz 2 tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	// TODO clamp actual throttle value so player can't over-drive
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

