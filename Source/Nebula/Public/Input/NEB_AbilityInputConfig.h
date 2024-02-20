// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

// Framework Includes
#include "GameplayTagContainer.h"

// Project Includes
#include "Definitions/NEB_InputDefinitions.h"

// Generated Header Included Last
#include "NEB_AbilityInputConfig.generated.h"

class UInputAction;

/**
 * Data Asset to configure Ability activated by Player Inputs
 */
UCLASS()
class NEBULA_API UNEB_AbilityInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UNEB_AbilityInputConfig();

#pragma region Ability Inputs

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ability Input Config")
	TArray<FNEB_AbilityInputConfigDefinition> AbilityInputConfig;

public:
	UInputAction* GetInputActionFromGameplayTag(const FGameplayTag& AbilityInputTag) const;

	const TArray<FNEB_AbilityInputConfigDefinition>& GetAbilityInputConfigDefinitions() const { return AbilityInputConfig; }

#pragma endregion Ability Inputs
};
