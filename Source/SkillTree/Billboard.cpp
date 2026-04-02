// Fill out your copyright notice in the Description page of Project Settings.


#include "Billboard.h"
#include "Components/WidgetComponent.h"
#include "TextDisplay.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABillboard::ABillboard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget");
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
}

void ABillboard::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (WidgetClass)
	{
		WidgetComponent->SetWidgetClass(WidgetClass);
		if (UTextDisplay* widget = Cast<UTextDisplay>(WidgetComponent->GetWidget()))
		{
			widget->SetText(Message);
		}
	}
}

// Called when the game starts or when spawned
void ABillboard::BeginPlay()
{
	Super::BeginPlay();
	
	if (WidgetClass)
	{
		WidgetComponent->SetWidgetClass(WidgetClass);
		if (UTextDisplay* widget = Cast<UTextDisplay>(WidgetComponent->GetWidget()))
		{
			widget->SetText(Message);
		}
	}
}

// Called every frame
void ABillboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FaceCamera)
	{
		return;
	}

	if (APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		WidgetComponent->SetWorldRotation(controller->PlayerCameraManager->GetCameraRotation().Quaternion());
		// Flip to face the camera
		WidgetComponent->AddLocalRotation(FQuat::MakeFromEuler({ 0, 0, 180.f }));
	}
}

