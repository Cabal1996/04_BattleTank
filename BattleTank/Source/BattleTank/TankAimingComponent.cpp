// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//This has coled in Tank.cpp to set Barrel pointer
void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

//Collecting Start Aim Location, End Aim Location, Speed and Calculating Launch Velocity
void UTankAimingComponent::AimLocation(FVector AimingLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }//pointer protection
	
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
	//Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator : %s"), *DeltaRotator.ToString())

	//Move the barrel the right amount this frame
	//Give a max elevation speed, and the frame time




	//Get access to turret and barrel
	//Create two rotators
	//Initialize rotators with data from AimLocation
	//Rotate turret and lift barrel



}