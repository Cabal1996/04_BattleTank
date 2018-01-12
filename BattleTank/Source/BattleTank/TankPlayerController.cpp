// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();

	if (!Tank)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possesing a Tank(Pawn)!!!"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("We controlle tank with name %s"), *Tank->GetName());
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
		UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString())
		
		//TODO Tell controlled tank to aim at that point
	}

	



}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Build a Ray-cast
		//Get Starter location
		//Get Ender location
			//
	//Output Hit result
	
	OutHitLocation = FVector(1.0f);

	return true;
}
