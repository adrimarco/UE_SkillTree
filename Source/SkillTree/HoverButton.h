// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HoverButton.generated.h"

class UButton;
class UProgressBar;
class UBorder;
class UTextBlock;

DECLARE_DELEGATE(FOnButtonPressed);

/**
 * 
 */
UCLASS()
class SKILLTREE_API UHoverButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Components
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> HoverButton;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBackground;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UBorder> ForegroundBorder;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock;

	// Animations
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> DisabledAnim;

	// Properties
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ActivationTime{ 1.f };

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText ButtonText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FontSize{ 16.f };

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool ButtonEnabled{ true };

	FOnButtonPressed OnButtonPressed;

protected:
	bool IsHovered{ false };

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void StartHover();

	UFUNCTION()
	void StopHover();

public:
	UFUNCTION()
	void SetEnabled(bool NewState);

	UFUNCTION()
	bool GetEnabled() const;

	UFUNCTION()
	void SetText(FText NewText);
};
