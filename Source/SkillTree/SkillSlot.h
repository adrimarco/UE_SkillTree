// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlot.generated.h"

class UBorder;
class UImage;
class UPaperSprite;

DECLARE_MULTICAST_DELEGATE(FOnUnlocked)

/**
 * 
 */
UCLASS()
class SKILLTREE_API USkillSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Components
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> SkillIcon;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UBorder> OuterBorder;

	// Animations
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> UnlockAnim;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> HoverAnim;

	// Properties
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UPaperSprite> Sprite;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USkillSlot* PreviousSkill;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLinearColor UnlockedColor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLinearColor BlockedColor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool IsPermanentlyUnlocked{ false };

	FLinearColor CurrentColor{FLinearColor::White};
	bool IsUnlocked{ false };
	bool IsHovered{ false };
	FOnUnlocked OnUnlocked;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	UFUNCTION()
	void Unlock();

	void SetWidgetColor(FLinearColor NewColor);
};
