// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextDisplay.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SKILLTREE_API UTextDisplay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Components
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock;

	void SetText(FText NewText);
};
