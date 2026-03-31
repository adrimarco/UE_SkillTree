// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeDisplay.h"

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
