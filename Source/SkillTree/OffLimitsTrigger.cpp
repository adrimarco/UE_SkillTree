// Fill out your copyright notice in the Description page of Project Settings.


#include "OffLimitsTrigger.h"
#include "SkillTreeCharacter.h"


AOffLimitsTrigger::AOffLimitsTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AOffLimitsTrigger::BeginPlay()
{
	OnActorBeginOverlap.AddDynamic(this, &AOffLimitsTrigger::OnTriggerEntered);
}

void AOffLimitsTrigger::OnTriggerEntered(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ASkillTreeCharacter* player = Cast<ASkillTreeCharacter>(OtherActor))
	{
		player->Respawn();
	}
}

