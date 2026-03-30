// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChargeIcon.generated.h"

/**
 * 
 */
UCLASS()
class SKILLTREE_API UChargeIcon : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// Animations
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FillAnim;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> EmptyAnim;

	// Properties
	bool IsFilled{ true };

public:
	UFUNCTION()
	void Fill();

	UFUNCTION()
	void Empty();
};
