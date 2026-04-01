// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "SkillTreeCharacter.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetGenerateOverlapEvents(true);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnTriggerEntered);

	SpawnNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Spawn Niagara"));
	SpawnNiagara->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	ApplyDefaultColor(true);
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::ApplyDefaultColor(bool UseDefault)
{
	SpawnNiagara->SetVariableLinearColor("Color", UseDefault ? DefaultColor : ActiveColor);
}

void ACheckpoint::OnTriggerEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASkillTreeCharacter* player = Cast<ASkillTreeCharacter>(OtherActor))
	{
		if (FirstTime)
		{
			ApplyDefaultColor(false);
			player->IncreaseSkillPoints();
			FirstTime = false;
		}

		player->SetRespawnLocation(GetActorLocation());
		player->RestoreCharges();
	}
}

