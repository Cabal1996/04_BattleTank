// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Classes/Engine/World.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Installing Aiming component to Tank BP by c++ code and get pointer to that component
	//No need to protect pointer as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
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
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	//Set a barrel
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

//Barrel pointer setter
void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	//Set a turret
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (!ProjectileBlueprint) { UE_LOG(LogTemp, Error, TEXT("No Projectile Blueprint installed!!!")); return; }
	if (Barrel && bIsReloaded)
	{
		//Spawn a projectile at the socket location on the barrel
		FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>
			(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}