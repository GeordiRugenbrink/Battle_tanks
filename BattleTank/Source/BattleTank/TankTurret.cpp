// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "engine/World.h"

void UTankTurret::AzimuthRotation(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Azimuth = RelativeRotation.Yaw + AzimuthChange;

	SetRelativeRotation(FRotator(0, Azimuth, 0));
}


