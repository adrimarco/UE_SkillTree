// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHud.generated.h"

class UModalMessage;
class UPlayerStats;
class UInputAction;

/**
 * 
 */
UCLASS()
class SKILLTREE_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Components
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UModalMessage> ModalMessage;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UPlayerStats> PlayerStatsDisplay;

	// Properties
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsSkillTreeVisible{ false };

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ToggleSkilTreeAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ToggleStatsAction;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void ToggleSkillTreeVisibility();

	UFUNCTION(BlueprintCallable)
	void ToggleStatsVisibility();

	UFUNCTION(BlueprintCallable)
	void ShowSkillTree();

	UFUNCTION(BlueprintCallable)
	void HideSkillTree();
};
