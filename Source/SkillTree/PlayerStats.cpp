// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStats.h"
#include "StatValue.h"
#include "Components/TextBlock.h"
#include "SkillTreeCharacter.h"

void UPlayerStats::NativeConstruct()
{
	Super::NativeConstruct();

	if (ASkillTreeCharacter* player = GetOwningPlayerPawn<ASkillTreeCharacter>())
	{
		player->OnSpeedChanged.BindUObject(this, &UPlayerStats::UpdateSpeedStat);
		player->OnJumpHeightChanged.BindUObject(this, &UPlayerStats::UpdateJumpStat);
		player->OnMaxChargesChanged.AddUObject(this, &UPlayerStats::UpdatePowerStat);
	}

	Tooltip->SetText("Hide Stats");
}

void UPlayerStats::SetExpanded(bool Expand)
{
	IsExpanded = Expand;

	ESlateVisibility displayVisibility = Expand ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
	SpeedDisplay->SetVisibility(displayVisibility);
	JumpDisplay->SetVisibility(displayVisibility);
	PowerDisplay->SetVisibility(displayVisibility);

	Tooltip->SetText(Expand ? "Hide Stats" : "Show Stats");
}

bool UPlayerStats::GetExpanded() const
{
	return IsExpanded;
}

void UPlayerStats::UpdateSpeedStat(float NewSpeed)
{
	SpeedDisplay->SetText(FString::Printf(TEXT("%.1f m/s"), NewSpeed / 100.f));
}

void UPlayerStats::UpdateJumpStat(float NewJumpHeight)
{
	JumpDisplay->SetText(FString::Printf(TEXT("%.1f m"), NewJumpHeight / 100.f));
}

void UPlayerStats::UpdatePowerStat(int NewPower)
{
	PowerDisplay->SetText(FString::Printf(TEXT("%d charges"), NewPower));
}
