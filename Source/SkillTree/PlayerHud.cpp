// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"
#include "EnhancedInputComponent.h"
#include "ModalMessage.h"
#include "HoverButton.h"
#include "PlayerStats.h"

void UPlayerHud::NativeConstruct()
{
	if (APlayerController* controller = GetOwningPlayer())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(controller->InputComponent)) {
			EnhancedInputComponent->BindAction(ToggleSkilTreeAction, ETriggerEvent::Triggered, this, &UPlayerHud::ToggleSkillTreeVisibility);
			EnhancedInputComponent->BindAction(ToggleStatsAction, ETriggerEvent::Triggered, this, &UPlayerHud::ToggleStatsVisibility);
		}
	}
}

void UPlayerHud::ToggleSkillTreeVisibility()
{
	if (IsSkillTreeVisible)
	{
		HideSkillTree();
	}
	else
	{
		ShowSkillTree();
	}
}

void UPlayerHud::ToggleStatsVisibility()
{
	PlayerStatsDisplay->SetExpanded(!PlayerStatsDisplay->GetExpanded());
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
