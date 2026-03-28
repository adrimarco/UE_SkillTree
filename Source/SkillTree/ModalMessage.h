// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ModalMessage.generated.h"

class UHoverButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SKILLTREE_API UModalMessage : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Components
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UHoverButton> AcceptButton;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UHoverButton> CloseButton;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> Message;

	// Animations
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeIn;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Show();

	UFUNCTION()
	void Close();

	void ConfigureAcceptButton(FText ButtonText, float ActivationTime, bool Enabled = true);
};
