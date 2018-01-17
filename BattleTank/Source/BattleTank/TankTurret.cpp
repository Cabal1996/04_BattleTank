// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Classes/Engine/World.h"

void UTankTurret::Turning(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto TurningChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewTurning = RelativeRotation.Yaw + TurningChange;
	SetRelativeRotation(FRotator(0, NewTurning, 0));
}

