// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OffLimitsTrigger.generated.h"

UCLASS()
class SKILLTREE_API AOffLimitsTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AOffLimitsTrigger();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Blueprintcallable)
	void OnTriggerEntered(AActor* OverlappedActor, AActor* OtherActor);
};
