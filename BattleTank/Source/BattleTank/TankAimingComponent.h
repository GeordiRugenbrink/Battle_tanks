// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EAimingState : uint8 {
	Reloading,
	Aiming,
	Ready
};

class UTankBarrel; //Forward declaration of the Tank Barrel
class UTankTurret;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void MoveBarrel(FVector AimDirection);

	void MoveTurret(FVector AimDirection);

	FRotator GetDeltaRotation(FVector AimDirection);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EAimingState AimingState = EAimingState::Reloading;
private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
