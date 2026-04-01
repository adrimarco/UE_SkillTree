// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillData.generated.h"

class UPaperSprite;

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	None,
	Speed,
	Power,
	Jump
};


USTRUCT(BlueprintType)
struct SKILLTREE_API FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPaperSprite> Sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor UnlockedColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};
