// Fill out your copyright notice in the Description page of Project Settings.


#include "ModalMessage.h"
#include "HoverButton.h"

void UModalMessage::NativeConstruct()
{
	CloseButton->OnButtonPressed.AddUObject(this, &UModalMessage::Close);
}

void UModalMessage::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(FadeIn);
	if (AcceptButton->GetEnabled())
	{
		AcceptButton->OnButtonPressed.AddUObject(this, &UModalMessage::Close);
	}
}

void UModalMessage::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
	AcceptButton->OnButtonPressed.Clear();
}

void UModalMessage::ConfigureAcceptButton(FText ButtonText, float ActivationTime, bool Enabled)
{
	AcceptButton->SetText(ButtonText);
	AcceptButton->SetEnabled(Enabled);
	if (Enabled)
	{
		AcceptButton->ActivationTime = ActivationTime;
	}
}
