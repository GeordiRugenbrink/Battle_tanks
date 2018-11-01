// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 *Holds barrel properties and the Elevate method
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent {
	GENERATED_BODY()

public:
	//-1 is max downward speed and +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreePerSeconds = 5;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevationDegrees = 0;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevationDegrees = 40;
};
