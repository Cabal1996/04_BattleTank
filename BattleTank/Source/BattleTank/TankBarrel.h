// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max down movement and +1 is max up movement
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreePerSecond = 10.0f; //sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegree = 35.0f; //sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegree = 0.0f; //sensible default
};
