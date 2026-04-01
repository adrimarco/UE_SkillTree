// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeDisplay.generated.h"

class UCanvasPanel;
class USkillSlot;
struct FSkillData;
class UTextBlock;
class UHoverButton;

/**
 * 
 */
UCLASS()
class SKILLTREE_API USkillTreeDisplay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Components
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> SkillsContainer;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillPointsTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UHoverButton> ResetButton;

	// Animations
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> IdleAnim;

	// Properties
	UPROPERTY(EditDefaultsOnly, Category="UI")
	float IdleAnimSpeed{ 0.5f };

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TObjectPtr<UDataTable> SkillsDataTable;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	void Show();
	void Hide();

	void OnSkillSelected(USkillSlot* SkillWidget);

	void OnResetSelected();

	// Blocks all unlocked skills and returns spent skill points
	void ResetSkillTree();

	void UpdateSkillPoints(int SkillPoints);
};
