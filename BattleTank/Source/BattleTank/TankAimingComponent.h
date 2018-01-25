// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward Declaration
class UTankBarrel;
class UTankTurret;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Initialization of barrel and turret
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	//Collecting Start Aim Location, End Aim Location, Speed and Calculating Launch Velocity
	void AimLocation(FVector WorldSpaceAim, float LaunchSpeed);


protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Locked;

private:
		
	//Pointer to Barrel has been set in tank.cpp
	UTankBarrel* Barrel = nullptr;

	//Pointer to Turret has been set in tank.cpp
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};
