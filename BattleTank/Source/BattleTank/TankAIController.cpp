// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h" //So we can implement OnDeath

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		//Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		if (AimingComponent->GetAimingState() == EAimingState::Ready) {
			AimingComponent->Fire();
		}
	}
}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }

		//TODO Subscribe our local method to tank's Death event
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("Receiving OnDeath!"));
}

