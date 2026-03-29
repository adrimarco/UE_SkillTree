// Fill out your copyright notice in the Description page of Project Settings.


#include "ModalMessage.h"
#include "HoverButton.h"

void UModalMessage::NativeConstruct()
{
	CloseButton->OnButtonPressed.BindUObject(this, &UModalMessage::Close);
	AcceptButton->OnButtonPressed.BindUObject(this, &UModalMessage::DoAccept);
}

void UModalMessage::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(FadeIn);
}

void UModalMessage::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
	OnAccept.Unbind();
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

void UModalMessage::DoAccept()
{
	OnAccept.ExecuteIfBound();

	Close();
}
