// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* AITank = GetAIControlledTank();

	if (!AITank)
	{
		UE_LOG(LogTemp, Error, TEXT("%s not possessing a Tank(Pawn)"), *(this->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s possessing %s"), *(this->GetName()), *AITank->GetName());
	}

	ATank* PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("%s have not aimed on Player"), *(this->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s have aimed on %s"), *(this->GetName()), *PlayerTank->GetName())
	}
}

ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


