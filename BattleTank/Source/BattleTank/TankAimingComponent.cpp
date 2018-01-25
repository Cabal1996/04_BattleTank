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
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	if (!BarrelToSet) { return; }

	Turret = TurretToSet;
	Barrel = BarrelToSet;
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
	}
	// if no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel || !Turret) { return; }
	//Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	
	//Elevation of barrel
	Barrel->Elevate(DeltaRotator.Pitch);

	//Turning of turret
	Turret->Turning(DeltaRotator.Yaw);
}
