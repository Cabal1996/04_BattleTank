// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Engine/World.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay()  override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	//Get pointer to tank BP which controlled by THIS controller
	ATank* GetAIControlledTank() const;

	//Get FVector which is a player position
	ATank* GetPlayerTank() const;
};
