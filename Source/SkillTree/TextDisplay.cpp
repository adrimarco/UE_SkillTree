// Fill out your copyright notice in the Description page of Project Settings.


#include "TextDisplay.h"
#include "Components/TextBlock.h"

void UTextDisplay::SetText(FText NewText)
{
	TextBlock->SetText(NewText);
}
