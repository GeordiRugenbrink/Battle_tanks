// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s YEET: Tank C++ Contruct"), *TankName);
}

void ATank::BeginPlay() {
	Super::BeginPlay(); //needed for BP to run
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s YEET: Tank C++ BeginPlay"), *TankName);
}

void ATank::AimAt(FVector HitLocation) {
	if (TankAimingComponent) {
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
}

void ATank::Fire() {
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (Barrel && IsReloaded) {
		//Spawn a Projectile at the socket location of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		if (!Projectile) {
			UE_LOG(LogTemp, Warning, TEXT("Projectile can't be found!"));
			return;
		}
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}