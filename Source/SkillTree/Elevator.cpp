// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Speed -= Gravity * DeltaTime;
	AddActorWorldOffset(FVector(0, 0, Speed * DeltaTime), false, nullptr, ETeleportType::TeleportPhysics);

	// Prevent from going below original position
	if (GetActorLocation().Z < InitialLocation.Z)
	{
		SetActorLocation(InitialLocation);
		Speed = 0.f;
	}
}

void AElevator::Activate()
{
	Speed = ActivationSpeed;
}

