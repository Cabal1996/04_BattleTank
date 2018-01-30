// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Classes/Engine/World.h"
#include "TankAimingComponent.h"

// Depends on movement component via path-finding system

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get Self tank pointer and Player tank pointer
	APawn* ControlledTank = GetPawn();
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	//Pointer protection
	if (!ensure(ControlledTank)) { UE_LOG(LogTemp, Error, TEXT("%s not possessing a Tank(Pawn)"), *(this->GetName())); return; }
	if (!ensure(AimingComponent)) { return; }
	if (ensure(PlayerTank))
	{
		//Move towards a player
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm

		//Aim towards a player
		
		AimingComponent->AimAt(PlayerTank->GetActorLocation()); // Parse coordinates of player to Tank.cpp

		//TODO fix firing
		//Fire if ready
		AimingComponent->Fire(); //TODO Don't fire every frame
	}
}



