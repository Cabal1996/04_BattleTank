// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Engine/EngineTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"// mast be the last include

/**
 * 
 */
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

private:
	//Get pointer to controlled Tank BP
	ATank* GetControlledTank() const;

	//Start the Tank moving the barrel so that a shot would hit where
	//the crosshair intersects the world
	void AimTowardsCrosshair();

	//Get world location of linetrace through crosshair, true if hits landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	//"De-project" the screen position of the crosshair to the world direction
	bool GetLookDirection(FVector2D CrosshairPosition, FVector& WorldDirection) const;

	//Get exact coordinates of hit location through line-trace
	bool GetLookVectorHitLocation(FVector WorldLocation, FVector& OUTHitLocation) const;

private:

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;
};
