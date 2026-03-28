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
		PlayerController->SetInputMode(FInputModeUIOnly());
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

void UPlayerHud::Test1()
{
	auto lambda = []() {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Magenta, "Test");
		}
	};
	ModalMessage->ConfigureAcceptButton(FText::FromString("Unlock"), 3.f);
	ModalMessage->AcceptButton->OnButtonPressed.AddLambda(lambda);
	ModalMessage->Show();
}

void UPlayerHud::Test3()
{
	auto lambda = []() {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Magenta, "Longer Test");
		}
	};

	ModalMessage->ConfigureAcceptButton(FText::FromString("Si si"), 6.f);
	ModalMessage->AcceptButton->OnButtonPressed.AddLambda(lambda);
	ModalMessage->Show();
}

void UPlayerHud::Test2()
{
	ModalMessage->ConfigureAcceptButton(FText::FromString("Chinga tu madre"), 0.f, false);
	ModalMessage->Show();
}
