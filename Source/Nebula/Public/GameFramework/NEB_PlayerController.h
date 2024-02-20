// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

// Generated Header Included Last
#include "NEB_PlayerController.generated.h"

struct FGameplayTag;
class UNEB_AbilityInputConfig;
class ANEB_PlayerCharacter;

/**
 * Base class for Player Controllers on Nebula Project
 */
UCLASS()
class NEBULA_API ANEB_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANEB_PlayerController();

#pragma region APlayerController

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

#pragma endregion APlayerController

#pragma region Ability Inputs

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Abilityh Inputs")
	TObjectPtr<UNEB_AbilityInputConfig> AbilityInputConfig;

	UFUNCTION()
	void OnAbilityInputPressed(FGameplayTag AbilityInputTag);

	UFUNCTION()
	void OnAbilityInputReleased(FGameplayTag AbilityInputTag);

	UFUNCTION()
	void OnAbilityInputHeld(FGameplayTag AbilityInputTag);

#pragma endregion Ability Inputs

#pragma region Core Properties

protected:
	TWeakObjectPtr<ANEB_PlayerCharacter> PlayerCharacterPtr;

#pragma endregion Core Properties

};
