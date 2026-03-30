// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChargesDisplay.generated.h"

class UChargeIcon;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class SKILLTREE_API UChargesDisplay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Components
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> IconsContainer;

	// Properties
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "UI")
	TSubclassOf<UChargeIcon> ItemClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	float IconsPadding{ 5.f };

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Game")
	int CurrentIconsCount{ 0 };

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateIconsCount(int MaxCount);

	void UpdateIconsVisibility(int ActiveCount);
};
