// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;
/**
 *
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	/*Moves the barrel of the tank towards the position of the crosshair
	so a shot can be fired to the position where the crosshair intersects the world*/
	void AimTowardsCrossHair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const;

private:
	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333f;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 10000000.0f; //in centimeters
};
