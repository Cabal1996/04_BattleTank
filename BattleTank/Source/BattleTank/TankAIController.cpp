// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "Classes/Engine/World.h"

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get Self tank pointer and Player tank pointer
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	//Pointer protection
	if (!ControlledTank) { UE_LOG(LogTemp, Error, TEXT("%s not possessing a Tank(Pawn)"), *(this->GetName())); return; }
	if (!PlayerTank) { UE_LOG(LogTemp, Error, TEXT("%s have not aimed on Player"), *(this->GetName())); return; }

	if (PlayerTank)
	{
		//TODO Move towards a player

		//Aim towards a player
		ControlledTank->AimAt(PlayerTank->GetActorLocation()); // Parse coordinates of player to Tank.cpp

		//Fire if ready
		ControlledTank->Fire(); //TODO Don't fire every frame
	}
}



