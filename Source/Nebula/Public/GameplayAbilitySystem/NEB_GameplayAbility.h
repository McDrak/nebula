// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Framework Includes
#include "Abilities/GameplayAbility.h"

// Generated Header Included Last
#include "NEB_GameplayAbility.generated.h"

/**
 * Base class for the Gameplay Abilities in the Nebula Project
 */
UCLASS()
class NEBULA_API UNEB_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UNEB_GameplayAbility();

#pragma region Input Tags

protected:
	/** Initial Gameplay Tag that identifies the Input Action used to activate the Ability */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Ability")
	FGameplayTag StartupInputTag;

public:
	FGameplayTag GetStartupInputTag() const { return StartupInputTag; }

#pragma endregion Input Tags
};
