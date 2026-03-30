// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargeIcon.h"

void UChargeIcon::Fill()
{
	if (!IsFilled)
	{
		PlayAnimation(FillAnim);
		IsFilled = true;
	}
}

void UChargeIcon::Empty()
{
	if (IsFilled)
	{
		PlayAnimation(EmptyAnim);
		IsFilled = false;
	}
}
