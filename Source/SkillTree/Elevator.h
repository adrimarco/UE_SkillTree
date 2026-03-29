// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

UCLASS()
class SKILLTREE_API AElevator : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Game")
	FVector InitialLocation{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	float Speed{0.f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	float Gravity{1500.f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	float ActivationSpeed{ 200.f };

public:	
	// Sets default values for this actor's properties
	AElevator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Activate();
};
