// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMesh.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Collecting Start Aim Location, End Aim Location, Speed and Calculating Launch Velocity
	void AimLocation(FVector WorldSpaceAim, float LaunchSpeed);

	//TODO add SetTurretReference

	//This has coled in Tank.cpp to set Barrel pointer
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

private:
	
	//Pointer to Barrel has been set in tank.cpp
	UStaticMeshComponent* Barrel = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	
};
