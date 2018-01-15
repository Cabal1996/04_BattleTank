// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Installing Aiming component to Tank BP by c++ code and get pointer to that component
	//No need to protect pointer as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Coled in Player/AI Controller. Parse Hit location vector to Aiming component
void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimLocation(HitLocation, LaunchSpeed);
}

//Barrel pointer setter
void ATank::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	//Set a barrel
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

