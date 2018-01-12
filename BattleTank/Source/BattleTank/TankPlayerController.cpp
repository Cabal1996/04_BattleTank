// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();

	if (!Tank)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a Tank(Pawn)!!!"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("We controlling tank with name %s"), *Tank->GetName());
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; } //pointer protection

	FVector HitLocation; // Out parameter

	//if its hit the landscape
	if (GetSightRayHitLocation(HitLocation)) //Has a "side-effect", is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString())
		
		//TODO Tell controlled tank to aim at that point
	}

}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find a crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairPosition = FVector2D(CrosshairXLocation * ViewportSizeX, CrosshairYLocation * ViewportSizeY);

	//"De-project" the screen position of the crosshair to the world direction
	FVector WorldLocation;
	if (GetLookDirection(CrosshairPosition, WorldLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look location: %s"), *WorldLocation.ToString());
	}
	
	
	//Line-trace along that look direction, and see what we hit (up to max range)
	return true;
}

//"De-project" the screen position of the crosshair to the world direction
bool ATankPlayerController::GetLookDirection(FVector2D CrosshairPosition, FVector& WorldDirection) const
{
	FVector WorldLocation; // for discarding
	return DeprojectScreenPositionToWorld(CrosshairPosition.X, CrosshairPosition.Y, WorldLocation, WorldDirection);
	
}