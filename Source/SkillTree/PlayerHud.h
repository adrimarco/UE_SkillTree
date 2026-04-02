// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHud.generated.h"

class UModalMessage;
class UPlayerStats;
class UInputAction;
class USkillTreeDisplay;
class UBackgroundBlur;
class USkillSlot;
class UStatValue;
struct FSkillData;

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

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<USkillTreeDisplay> SkillTree;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UBackgroundBlur> SkillTreeBackground;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UStatValue> SkillPointNotify;

	// Animations
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> NewSkillPointAnim;

	// Properties
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsSkillTreeVisible{ false };

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ToggleSkilTreeAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ToggleStatsAction;

	static UPlayerHud* ActivePlayerHud;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void ToggleSkillTreeVisibility();

	UFUNCTION(BlueprintCallable)
	void ToggleStatsVisibility();

	UFUNCTION(BlueprintCallable)
	void ShowSkillTree();

	UFUNCTION(BlueprintCallable)
	void HideSkillTree();

	static UModalMessage* GetHudModalMessage();
	static void PlayNotification(FString NotificationText);
};
