// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn {
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	//TODO remove once firing is moved to aiming


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3.0f;

	//Local Barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; //TODO Remove this

	double LastFireTime = 0;
};
