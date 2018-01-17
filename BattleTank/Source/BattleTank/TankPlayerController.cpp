// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"


// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();

	if (!Tank)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a Tank(Pawn)!!!"));
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

//Get pointer to controlled Tank BP
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

//Start the Tank moving the barrel so that a shot would hit where
//the crosshair intersects the world
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; } //pointer protection

	FVector HitLocation; // Out parameter

	//if its hit the landscape
	if (GetSightRayHitLocation(HitLocation)) //Has a "side-effect", is going to line trace
	{
		GetControlledTank()->AimAt(HitLocation); // Parse coordinates of HIT Location to Tank.cpp
	}

}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find a crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairPosition = FVector2D(CrosshairXLocation * ViewportSizeX, CrosshairYLocation * ViewportSizeY);

	//"De-project" the screen position of the crosshair to the world direction
	FVector WorldLocation;
	if (GetLookDirection(CrosshairPosition, WorldLocation))
	{
		//Line-trace along that look direction, and see what we hit (up to max range)
		if (GetLookVectorHitLocation(WorldLocation, OutHitLocation))
		{
			return true;
		}
	}
	return false;
}

//"De-project" the screen position of the crosshair to the world direction
bool ATankPlayerController::GetLookDirection(FVector2D CrosshairPosition, FVector& WorldDirection) const
{
	FVector WorldLocation; // for discarding
	return DeprojectScreenPositionToWorld(CrosshairPosition.X, CrosshairPosition.Y, WorldLocation, WorldDirection);
	
}

//Get exact coordinates of hit location through line-trace
bool ATankPlayerController::GetLookVectorHitLocation(FVector WorldLocation, FVector& OUTHitLocation) const
{
	//Defining Start and end location
	FVector LineStart = PlayerCameraManager->GetCameraLocation();
	FVector LineEnd = LineStart + WorldLocation * LineTraceRange;

	//DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor(255, 0, 0, 255), false, 0.0f, 0.0f, 5.0f); //Debugging tool

	//Setup query parameters OPTIONAL
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetControlledTank());
	
	//Setup collision parameters OPTIONAL
	//FCollisionResponseParams ResponseParams(ECollisionResponse::ECR_Block);

	// OUT parameter
	FHitResult HitResult;

	//Getting result of HIT
	if (GetWorld()->LineTraceSingleByChannel(HitResult, 
											LineStart,
											LineEnd,
											ECollisionChannel::ECC_Visibility,
											TraceParameters
											))
	{
		OUTHitLocation = HitResult.ImpactPoint;
		return true;
	}
	
	OUTHitLocation = FVector(0);
	return false;
}
