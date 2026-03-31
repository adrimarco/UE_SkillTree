// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStats.generated.h"

class UTextBlock;
class UStatValue;

/**
 * 
 */
UCLASS()
class SKILLTREE_API UPlayerStats : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Components
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UStatValue> Tooltip;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UStatValue> SpeedDisplay;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UStatValue> JumpDisplay;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UStatValue> PowerDisplay;

	//Properties
	bool IsExpanded{ true };

protected:
	virtual void NativeConstruct() override;

public:
	void SetExpanded(bool Expand);
	bool GetExpanded() const;

	void UpdateSpeedStat(float NewSpeed);
	void UpdateJumpStat(float NewJumpHeight);
	void UpdatePowerStat(int NewPower);
};
