// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


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

