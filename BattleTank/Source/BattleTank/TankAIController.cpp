// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "Classes/Engine/World.h"

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	ATank* AITank = GetAIControlledTank();

	if (!AITank)
	{
		UE_LOG(LogTemp, Error, TEXT("%s not possessing a Tank(Pawn)"), *(this->GetName()));
	}

	ATank* PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("%s have not aimed on Player"), *(this->GetName()));
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


