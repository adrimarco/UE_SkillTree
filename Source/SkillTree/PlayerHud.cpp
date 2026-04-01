// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"
#include "EnhancedInputComponent.h"
#include "ModalMessage.h"
#include "HoverButton.h"
#include "PlayerStats.h"
#include "SkillTreeDisplay.h"
#include "SkillSlot.h"
#include "SkillData.h"
#include "Components/BackgroundBlur.h"

UModalMessage* UPlayerHud::ModalMessageInstance = nullptr;

void UPlayerHud::NativeConstruct()
{
	if (APlayerController* controller = GetOwningPlayer())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(controller->InputComponent)) {
			EnhancedInputComponent->BindAction(ToggleSkilTreeAction, ETriggerEvent::Triggered, this, &UPlayerHud::ToggleSkillTreeVisibility);
			EnhancedInputComponent->BindAction(ToggleStatsAction, ETriggerEvent::Triggered, this, &UPlayerHud::ToggleStatsVisibility);
		}
	}

	ModalMessageInstance = ModalMessage;
}

void UPlayerHud::NativeDestruct()
{
	Super::NativeDestruct();

	if (ModalMessageInstance == ModalMessage)
	{
		ModalMessageInstance = nullptr;
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
	// Modal message can be requested
	ModalMessageInstance = ModalMessage;

	APlayerController* PlayerController = GetOwningPlayer<APlayerController>();
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
	}

	SkillTree->Show();
	SkillTreeBackground->SetVisibility(ESlateVisibility::Visible);

	IsSkillTreeVisible = true;
}

void UPlayerHud::HideSkillTree()
{
	// In case it is shown, ensures modal message closes
	ModalMessage->Close();

	// Modal message can no longer be accessed
	if (ModalMessageInstance == ModalMessage)
	{
		ModalMessageInstance = nullptr;
	}

	APlayerController* PlayerController = GetOwningPlayer<APlayerController>();
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}

	SkillTree->Hide();
	SkillTreeBackground->SetVisibility(ESlateVisibility::Collapsed);

	IsSkillTreeVisible = false;
}
