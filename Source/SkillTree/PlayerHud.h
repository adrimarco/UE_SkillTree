// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHud.generated.h"

class UModalMessage;

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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsSkillTreeVisible{ false };

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void ShowSkillTree();

	UFUNCTION(BlueprintCallable)
	void HideSkillTree();
};
