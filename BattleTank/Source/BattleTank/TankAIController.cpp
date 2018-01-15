// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"


// Called when the game starts or when spawned
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

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		//TODO Move towards a player

		//Aim towards a player
		GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation()); // Parse coordinates of player to Tank.cpp

		//TODO Fire if ready
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


