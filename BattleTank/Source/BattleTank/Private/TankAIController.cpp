// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"


ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
};

ATank* ATankAIController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
};

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp,Warning,TEXT("AITankController is not possesing"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s AITankController is possesing"),*(ControlledTank->GetName()));
	}
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank is not Found by %s"),*(GetControlledTank()->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s PlayerTank is Found by %s "),*(GetPlayerTank()->GetName()), *(GetControlledTank()->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TODO move towards the player

	//aim towards to player
	if (GetPlayerTank()) { 
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
	//fire if ready
}
