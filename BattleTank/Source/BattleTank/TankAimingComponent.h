// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	//Initialization of barrel and turret
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float LaunchSpeed = 4000.0f;

	//Collecting Start Aim Location, End Aim Location, Speed and Calculating Launch Velocity
	//Coled in Player/AI Controller. Parse Hit location vector to Aiming component
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
		
	//Pointer to Barrel has been set in tank.cpp
	UTankBarrel* Barrel = nullptr;

	//Pointer to Turret has been set in tank.cpp
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; // Set in BP of Tank

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ReloadTimeInSeconds = 3.0f;

	FVector AimDirection;

	double LastFireTime = 0;

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();

};
