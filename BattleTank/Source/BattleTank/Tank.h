// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:

	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Coled in Player/AI Controller. Parse Hit location vector to Aiming component
	void AimAt(FVector HitLocation);

	//Barrel pointer setter
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet); // Coled from BP Event Graph

private:

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000.0f; //TODO find sensible default
	
};
