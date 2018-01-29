// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "Classes/Engine/World.h"

// Depends on movement component via path-finding system

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
	if (!ensure(ControlledTank)) { UE_LOG(LogTemp, Error, TEXT("%s not possessing a Tank(Pawn)"), *(this->GetName())); return; }
	if (ensure(PlayerTank))
	{
		//Move towards a player
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm

		//Aim towards a player
		ControlledTank->AimAt(PlayerTank->GetActorLocation()); // Parse coordinates of player to Tank.cpp

		//Fire if ready
		//ControlledTank->Fire(); //TODO Don't fire every frame
	}
}



