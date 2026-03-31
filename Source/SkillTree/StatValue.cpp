// Fill out your copyright notice in the Description page of Project Settings.


#include "StatValue.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PaperSprite.h"

void UStatValue::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Icon && Sprite)
	{
		Icon->SetBrushFromAtlasInterface(Sprite);
	}
}

void UStatValue::SetTextByInt(int Value)
{
	TextValue->SetText(FText::FromString(FString::FromInt(Value)));
}

void UStatValue::SetTextByFloat(float Value)
{
	TextValue->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), Value)));
}

void UStatValue::SetText(FString Value)
{
	TextValue->SetText(FText::FromString(Value));
}
