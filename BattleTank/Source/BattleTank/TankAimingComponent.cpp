// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Classes/Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//This has coled in Tank.cpp to set Barrel pointer
void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

//This has coled in Tank.cpp to set Turret pointer
void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

//Collecting Start Aim Location, End Aim Location, Speed and Calculating Launch Velocity
void UTankAimingComponent::AimLocation(FVector AimingLocation, float LaunchSpeed)
{
	
	if (!Barrel) { UE_LOG(LogTemp, Error, TEXT("%s : NO BARREL"), *GetOwner()->GetName()); return; }//pointer protection
	if (!Turret) { UE_LOG(LogTemp, Error, TEXT("%s : NO TURRET"), *GetOwner()->GetName()); return; }//pointer protection

	FVector OutLaunchVelocity; //OUT parameter
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculation of Launch Velocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		AimingLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		TurnTurretTowards(AimDirection);
	}
	// if no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	
	//Elevation of barrel
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::TurnTurretTowards(FVector AimDirection)
{
	//Work-out difference between current barrel rotation and AimDirection
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotator - TurretRotation;

	//Turning of turret
	Turret->Turning(DeltaRotation.Yaw);
}