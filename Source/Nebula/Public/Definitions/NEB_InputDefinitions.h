// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Framework Includes
#include "GameplayTagContainer.h"

// Generated Header Included Last
#include "NEB_InputDefinitions.generated.h"

class UInputAction;

/**
 * Struct to define Gameplay Abilities that matches the tag when the Input Action is pressed
 */
USTRUCT(Blueprintable, BlueprintType)
struct FNEB_AbilityInputConfigDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Ability Input Config")
	FGameplayTag AbilityInputTag;

	UPROPERTY(EditAnywhere, Category = "Ability Input Config")
	TObjectPtr<UInputAction> AbilityInputAction;

	FNEB_AbilityInputConfigDefinition()
		: AbilityInputAction(nullptr)
	{
	}
};
