// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"




ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		//TODO tell controlled tank to aim at this point 
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.f);
	//find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	FVector2D ScreenLocation;
	GetViewportSize(
		ViewportSizeX,
		ViewportSizeY
	);
	ScreenLocation = FVector2D(
		ViewportSizeX*CrossHairXLocation,
		ViewportSizeY*CrossHairYLocation
	);
	
	//"De-Project" the screen positiom of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//Line-trace along that look direction,and see what we hit(up to max range)
		if (GetLookVectorHitLocation(LookDirection, OutHitLocation)) {
			GetControlledTank()->AimAt(OutHitLocation);
		}
	}
	

	// if crosshair hit something OutHitLocation will be hit location
	//else
 	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;//this will not use
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult OutHit;
	FVector LineStart = PlayerCameraManager->GetCameraLocation();
	FVector LineEnd = LineStart + (LookDirection * LineTraceRange);
	if (GetWorld()->
			LineTraceSingleByChannel(
				OutHit,
				LineStart,
				LineEnd,
				ECollisionChannel::ECC_Visibility
			)
		) {
		HitLocation = OutHit.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank =GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerTankController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerTankController is possesing %s"), *(ControlledTank->GetName()));
	}
	
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}