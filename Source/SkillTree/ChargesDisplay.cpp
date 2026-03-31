// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargesDisplay.h"
#include "SkillTreeCharacter.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "ChargeIcon.h"

void UChargesDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	if (ASkillTreeCharacter* player = Cast<ASkillTreeCharacter>(GetOwningPlayerPawn()))
	{
		player->OnMaxChargesChanged.AddUObject(this, &UChargesDisplay::UpdateIconsCount);
		player->OnChargesCountChanged.BindUObject(this, &UChargesDisplay::UpdateIconsVisibility);

		//UpdateIconsCount(player->GetMaxCharges());
		//UpdateIconsVisibility(player->GetCurrentCharges());
	}

	check(ItemClass);
}

void UChargesDisplay::UpdateIconsCount(int MaxCount)
{
	CurrentIconsCount = MaxCount;

	// When charges count increases, creates new icons
	while (CurrentIconsCount > IconsContainer->GetChildrenCount())
	{
		UChargeIcon* newIcon = CreateWidget<UChargeIcon>(GetWorld(), ItemClass);
		UHorizontalBoxSlot* newIconSlot = IconsContainer->AddChildToHorizontalBox(newIcon);
		newIconSlot->SetPadding(FMargin(IconsPadding));
		newIcon->Fill();
	}

	int iconsCount = IconsContainer->GetChildrenCount();
	for (int i=0; i<iconsCount; ++i)
	{
		IconsContainer->GetChildAt(i)->SetVisibility(i < CurrentIconsCount ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UChargesDisplay::UpdateIconsVisibility(int ActiveCount)
{
	int iconsCount = IconsContainer->GetChildrenCount();
	for (int i = 0; i < iconsCount; ++i)
	{
		if (UChargeIcon* Icon = Cast<UChargeIcon>(IconsContainer->GetChildAt(i)))
		{
			if (i < ActiveCount)
			{
				Icon->Fill();
			}
			else
			{
				Icon->Empty();
			}
		}
	}
}
