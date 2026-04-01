// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeDisplay.h"
#include "Components/CanvasPanel.h"
#include "SkillSlot.h"
#include "SkillData.h"
#include "SkillTreeCharacter.h"
#include "PlayerHud.h"
#include "ModalMessage.h"
#include "Components/TextBlock.h"
#include "HoverButton.h"

void USkillTreeDisplay::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (SkillsDataTable && SkillsDataTable->GetRowStruct() == FSkillData::StaticStruct())
	{
		// Fill each skill slot with the information in the skills data table
		TArray<UWidget*> widgets = SkillsContainer->GetAllChildren();
		for (UWidget* widget : widgets)
		{
			USkillSlot* skillWidget = Cast<USkillSlot>(widget);
			if (!skillWidget || skillWidget->SkillID.IsNone())
			{
				continue;
			}
			
			if (FSkillData* skillData = SkillsDataTable->FindRow<FSkillData>(skillWidget->SkillID, {}))
			{
				skillWidget->SetUnlockedColor(skillData->UnlockedColor);
				skillWidget->SetSprite(skillData->Sprite);
			}
		}
	}
}

void USkillTreeDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	// Bound function requires to check the data table, so checks the type before doing the binding
	if (SkillsDataTable && SkillsDataTable->GetRowStruct() == FSkillData::StaticStruct())
	{
		TArray<UWidget*> widgets = SkillsContainer->GetAllChildren();
		for (UWidget* widget : widgets)
		{
			USkillSlot* skillWidget = Cast<USkillSlot>(widget);
			if (!skillWidget || skillWidget->SkillID.IsNone())
			{
				continue;
			}

			skillWidget->OnSelected.BindUObject(this, &USkillTreeDisplay::OnSkillSelected);
		}
	}

	if (ASkillTreeCharacter* player = Cast<ASkillTreeCharacter>(GetOwningPlayerPawn()))
	{
		player->OnSkillPointsChanged.BindUObject(this, &USkillTreeDisplay::UpdateSkillPoints);
	}

	ResetButton->OnButtonPressed.BindUObject(this, &USkillTreeDisplay::OnResetSelected);
	ResetButton->SetVisibility(ESlateVisibility::Collapsed);
}

void USkillTreeDisplay::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(IdleAnim, 0.f, 0, EUMGSequencePlayMode::Forward, IdleAnimSpeed);
}

void USkillTreeDisplay::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
	StopAnimation(IdleAnim);
}

void USkillTreeDisplay::OnSkillSelected(USkillSlot* SkillWidget)
{
	if (!SkillWidget)
	{
		return;
	}

	if (FSkillData* skillData = SkillsDataTable->FindRow<FSkillData>(SkillWidget->SkillID, {}))
	{
		UModalMessage* ModalMessage = UPlayerHud::GetModalMessage();
		if (!ModalMessage)
		{
			return;
		}

		FString skillMessage = FString::Printf(TEXT("%s\n\n%s\n\nSkill Points: %s/1"), 
			*skillData->Name.ToString(), 
			*skillData->Description.ToString(), 
			*SkillPointsTag->GetText().ToString()
		);
		ModalMessage->SetText(FText::FromString(skillMessage));

		if (SkillWidget->IsUnlocked)
		{
			ModalMessage->ConfigureAcceptButton(FText::FromString("Already Unlocked"), 0, false);
		}
		else if (SkillWidget->PreviousSkill && !SkillWidget->PreviousSkill->IsUnlocked)
		{
			ModalMessage->ConfigureAcceptButton(FText::FromString("Locked"), 0, false);
		}
		else
		{
			ASkillTreeCharacter* player = Cast<ASkillTreeCharacter>(GetOwningPlayerPawn());

			if (!player || !player->HasSkillPoints())
			{
				ModalMessage->ConfigureAcceptButton(FText::FromString("Skill Points Required"), 0, false);
			}
			else
			{
				ModalMessage->ConfigureAcceptButton(FText::FromString("Unlock"), 1.f);
				ModalMessage->OnAccept.BindLambda([SkillWidget, skillData, player, this]() {
					player->DecreaseSkillPoints();
					player->AddUpgrade(skillData->Type, skillData->Value);

					SkillWidget->Unlock();
					ResetButton->SetVisibility(ESlateVisibility::Visible);
				});
			}
		}

		ModalMessage->Show();
	}
}

void USkillTreeDisplay::OnResetSelected()
{
	UModalMessage* ModalMessage = UPlayerHud::GetModalMessage();
	if (!ModalMessage)
	{
		return;
	}

	ModalMessage->SetText(FText::FromString("Are you sure you want to reset the skill tree?\n\nYou will recover all your skill points."));
	ModalMessage->ConfigureAcceptButton(FText::FromString("Reset"), 5.f);
	ModalMessage->OnAccept.BindUObject(this, &USkillTreeDisplay::ResetSkillTree);
	ModalMessage->Show();
}

void USkillTreeDisplay::ResetSkillTree()
{
	ASkillTreeCharacter* player = Cast<ASkillTreeCharacter>(GetOwningPlayerPawn());
	if (!player)
	{
		return;
	}

	int skillPoints{ 0 };
	TMap<ESkillType, float> skillsValue;
	TArray<UWidget*> widgets = SkillsContainer->GetAllChildren();
	// Accumulates all skills values unlocked in the map to undo the upgrades all at once
	for (UWidget* widget : widgets)
	{
		USkillSlot* skillWidget = Cast<USkillSlot>(widget);
		if (!skillWidget || skillWidget->SkillID.IsNone() || !skillWidget->IsUnlocked)
		{
			continue;
		}
		FSkillData* skillData = SkillsDataTable->FindRow<FSkillData>(skillWidget->SkillID, {});
		if (!skillData)
		{
			continue;
		}

		float currentValue = skillsValue.FindOrAdd(skillData->Type);
		skillsValue[skillData->Type] = currentValue + skillData->Value;
		skillPoints++;
		skillWidget->Block();
	}

	for (const TPair<ESkillType, float>& pair : skillsValue)
	{
		player->RemoveUpgrade(pair.Key, pair.Value);
	}

	player->IncreaseSkillPoints(skillPoints);
	ResetButton->SetVisibility(ESlateVisibility::Hidden);
}

void USkillTreeDisplay::UpdateSkillPoints(int SkillPoints)
{
	SkillPointsTag->SetText(FText::FromString(FString::FromInt(SkillPoints)));
}
