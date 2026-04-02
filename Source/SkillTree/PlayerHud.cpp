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
#include "StatValue.h"

UPlayerHud* UPlayerHud::ActivePlayerHud = nullptr;

void UPlayerHud::NativeConstruct()
{
	if (APlayerController* controller = GetOwningPlayer())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(controller->InputComponent)) {
			EnhancedInputComponent->BindAction(ToggleSkilTreeAction, ETriggerEvent::Triggered, this, &UPlayerHud::ToggleSkillTreeVisibility);
			EnhancedInputComponent->BindAction(ToggleStatsAction, ETriggerEvent::Triggered, this, &UPlayerHud::ToggleStatsVisibility);
		}
	}

	SkillPointNotify->SetVisibility(ESlateVisibility::Collapsed);
	ActivePlayerHud = this;
}

void UPlayerHud::NativeDestruct()
{
	Super::NativeDestruct();

	if (ActivePlayerHud == this)
	{
		ActivePlayerHud = nullptr;
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

	SkillTree->Show();
	SkillTreeBackground->SetVisibility(ESlateVisibility::Visible);

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

	SkillTree->Hide();
	SkillTreeBackground->SetVisibility(ESlateVisibility::Collapsed);

	IsSkillTreeVisible = false;
}

UModalMessage* UPlayerHud::GetHudModalMessage()
{
	return ActivePlayerHud ? ActivePlayerHud->ModalMessage : nullptr;
}

void UPlayerHud::PlayNotification(FString NotificationText)
{
	if (ActivePlayerHud)
	{
		ActivePlayerHud->SkillPointNotify->SetText(NotificationText);
		ActivePlayerHud->PlayAnimation(ActivePlayerHud->NewSkillPointAnim);
	}
}
