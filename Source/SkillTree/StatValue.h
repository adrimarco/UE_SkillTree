// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatValue.generated.h"


class UTextBlock;
class UPaperSprite;
class UImage;

/**
 * 
 */
UCLASS()
class SKILLTREE_API UStatValue : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Components
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextValue;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> Icon;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UPaperSprite> Sprite;

protected:
	virtual void NativePreConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetTextByInt(int Value);

	UFUNCTION(BlueprintCallable)
	void SetTextByFloat(float Value);

	UFUNCTION(BlueprintCallable)
	void SetText(FString Value);
};
