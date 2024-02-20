// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Framework Includes
#include "AbilitySystemComponent.h"

// Generated Header Included Last
#include "NEB_AbilitySystemComponent.generated.h"

/**
 * Base class for the Ability System Component in the Nebula Project
 */
UCLASS()
class NEBULA_API UNEB_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UNEB_AbilitySystemComponent();

#pragma region Startup

protected:
	/** If true, the initial abilities has been granted to the owner/avatar of this component */
	uint8 bWereInitialAbilitiesGranted : 1;

	/** If true, the startup effects has been applied to the owner/avatar of this component */
	uint8 bWereStartupEffectsApplied : 1;

public:
	bool WereInitialAbilitiesGranted() const { return bWereInitialAbilitiesGranted; }
	bool WereStartupEffectsApplied() const { return bWereStartupEffectsApplied; }
	void SetInitialAbilitiesGranted(const bool bNewInitialAbilitiesGranted) { bWereInitialAbilitiesGranted = bNewInitialAbilitiesGranted; }
	void SetStartupEffectsApplied(const bool bNewStartupEffectsApplied) { bWereStartupEffectsApplied = bNewStartupEffectsApplied; }

#pragma endregion Startup

#pragma region Ability Inputs

	void OnAbilityInputPressed(const FGameplayTag& AbilityInputTag);
	void OnAbilityInputReleased(const FGameplayTag& AbilityInputTag);
	void OnAbilityInputHeld(const FGameplayTag& AbilityInputTag);

#pragma endregion Ability Inputs

};
