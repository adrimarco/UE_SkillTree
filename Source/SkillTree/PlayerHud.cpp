// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"
#include "ModalMessage.h"
#include "HoverButton.h"

void UPlayerHud::NativeConstruct()
{
	
}

void UPlayerHud::ShowSkillTree()
{
	APlayerController* PlayerController = GetOwningPlayer<APlayerController>();
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
	}

	IsSkillTreeVisible = true;
}

void UPlayerHud::HideSkillTree()
{
	// In case it is shown, ensures modal message closes
	ModalMessage->Close();

	APlayerController* PlayerController = GetOwningPlayer<APlayerController>();
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}

	IsSkillTreeVisible = false;
}
