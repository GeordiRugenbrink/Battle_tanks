// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();

	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentAmmo <= 0) {
		AimingState = EAimingState::NoAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds) {
		AimingState = EAimingState::Reloading;
	}
	else if (IsBarrelMoving()) {
		AimingState = EAimingState::Aiming;
	}
	else {
		AimingState = EAimingState::Ready;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	//Calculate the OutLaunchvelocity
	if (bHaveAimSolution) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
}

void UTankAimingComponent::Fire() {
	//bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (AimingState == EAimingState::Ready || AimingState == EAimingState::Aiming) {
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }
		//Spawn a Projectile at the socket location of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		CurrentAmmo--;
	}
}

EAimingState UTankAimingComponent::GetAimingState() const {
	return AimingState;
}

int UTankAimingComponent::GetAmmoLeft() const {
	return CurrentAmmo;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	if (!ensure(Barrel)) { return; }
	auto DeltaRotator = GetDeltaRotation(AimDirection);

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection) {
	if (!ensure(Turret)) { return; }
	auto DeltaRotator = GetDeltaRotation(AimDirection);
	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->AzimuthRotation(DeltaRotator.Yaw);
	}
	else {
		Turret->AzimuthRotation(-DeltaRotator.Yaw);
	}
}

FRotator UTankAimingComponent::GetDeltaRotation(FVector AimDirection) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	return DeltaRotator;
}