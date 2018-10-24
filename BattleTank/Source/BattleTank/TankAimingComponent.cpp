// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();


}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchvelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0,
		ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	//Calculate difference between current rotation and the Aimdirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;


	Barrel->Elevate(DeltaRotator.Pitch);
}