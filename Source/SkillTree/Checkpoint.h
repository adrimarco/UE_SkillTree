// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

class UNiagaraComponent;
class UBoxComponent;

UCLASS()
class SKILLTREE_API ACheckpoint : public AActor
{
	GENERATED_BODY()

public:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNiagaraComponent* SpawnNiagara;

	// Properties
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FLinearColor DefaultColor;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FLinearColor ActiveColor;

	// If it's true, checkpoint has never been activated
	bool FirstTime{ true };

public:	
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ApplyDefaultColor(bool UseDefault);

	UFUNCTION(Blueprintcallable)
	void OnTriggerEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
