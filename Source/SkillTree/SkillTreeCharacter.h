// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SkillTreeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UNiagaraComponent;
class UInputAction;
struct FInputActionValue;
class UPlayerHud;
class AElevator;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaxChargesChanged, int /* MaxCharges */);
DECLARE_DELEGATE_OneParam(FOnChargesCountChanged, int /* Charges */);
DECLARE_DELEGATE_OneParam(FOnSpeedChanged, float /* Speed */);
DECLARE_DELEGATE_OneParam(FOnJumpHeightChanged, float /* Jump Height */);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class ASkillTreeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Niagara */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* AbilityNiagara;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	/** Ability Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AbilityAction;

	
	// UI
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UPlayerHud> HudWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UPlayerHud> HudInstance;

	// Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	int Charges{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	int MaxCharges{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	float AbilityRadius{ 300.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	TSubclassOf<AElevator> AbilityTarget;

public:
	FOnMaxChargesChanged OnMaxChargesChanged;
	FOnChargesCountChanged OnChargesCountChanged;
	FOnSpeedChanged OnSpeedChanged;
	FOnJumpHeightChanged OnJumpHeightChanged;

public:

	/** Constructor */
	ASkillTreeCharacter();	

	virtual void BeginPlay() override;

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	UFUNCTION(BlueprintCallable)
	void UseAbility();

	UFUNCTION()
	int GetCurrentCharges() const { return Charges; }

	UFUNCTION()
	int GetMaxCharges() const { return MaxCharges; }

	UFUNCTION()
	void SetMaxCharges(int NewMaxChargesCount);

	UFUNCTION()
	void SetCharges(int NewChargesCount);

	UFUNCTION(BlueprintCallable)
	void RestoreCharges();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

