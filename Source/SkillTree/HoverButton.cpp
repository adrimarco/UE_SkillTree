// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverButton.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"


void UHoverButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock->SetText(ButtonText);
	FSlateFontInfo FontData = TextBlock->GetFont();
	FontData.Size = FontSize;
	TextBlock->SetFont(FontData);
}

void UHoverButton::NativeConstruct()
{
	Super::NativeConstruct();

	HoverButton->OnPressed.AddDynamic(this, &UHoverButton::StartHover);
	HoverButton->OnReleased.AddDynamic(this, &UHoverButton::StopHover);
	
	ForegroundBorder->SetVisibility(ESlateVisibility::Hidden);
	SetEnabled(ButtonEnabled);
}

void UHoverButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!ButtonEnabled)
	{
		return;
	}

	float CurrentPercent = ProgressBackground->GetPercent();
	if (IsHovered)
	{
		if (ActivationTime <= 0.f)
		{
			CurrentPercent = 1.f;
		}
		else
		{
			CurrentPercent += InDeltaTime / ActivationTime;
		}

		if (CurrentPercent >= 0.9999f)
		{
			// Hovered long enough: Button activated
			OnButtonPressed.ExecuteIfBound();
			IsHovered = false;
			CurrentPercent = 0.f;
		}
	}
	else if (CurrentPercent > 0.f)
	{
		CurrentPercent = FMath::Max(0.f, CurrentPercent - InDeltaTime);
	}

	ProgressBackground->SetPercent(CurrentPercent);
}

void UHoverButton::StartHover()
{
	if (ButtonEnabled)
	{
		IsHovered = true;
		ForegroundBorder->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		if (!IsPlayingAnimation())
		{
			PlayAnimation(DisabledAnim, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f, true);
		}
	}
}

void UHoverButton::StopHover()
{
	IsHovered = false;
	ForegroundBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UHoverButton::SetEnabled(bool NewState)
{
	ButtonEnabled = NewState;
	if (!NewState)
	{
		ProgressBackground->SetPercent(0.f);
	}
}

bool UHoverButton::GetEnabled() const
{
	return ButtonEnabled;
}

void UHoverButton::SetText(FText NewText)
{
	ButtonText = NewText;
	TextBlock->SetText(NewText);
}
