// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeDisplay.generated.h"

/**
 * 
 */
UCLASS()
class SKILLTREE_API USkillTreeDisplay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Animations
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> IdleAnim;

	// Properties
	UPROPERTY(EditDefaultsOnly, Category="UI")
	float IdleAnimSpeed{ 0.5f };

	void Show();
	void Hide();
};
