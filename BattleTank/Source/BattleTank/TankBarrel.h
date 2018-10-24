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
	void Elevate(float DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreePerSeconds = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 40;
};
