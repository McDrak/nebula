// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Framework Includes
#include "AbilitySystemGlobals.h"

// Generated Header Included Last
#include "NEB_AbilitySystemGlobals.generated.h"

/**
 * Ability System Globals class for Nebula Project
 */
UCLASS()
class NEBULA_API UNEB_AbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	UNEB_AbilitySystemGlobals();

#pragma region UAbilitySystemGlobals

public:
	virtual void ReloadAttributeDefaults() override;

	void InitAttributeSetDefaults(UAbilitySystemComponent* AbilitySystemComponent, const FName& GroupName, const int32 Level, const bool bInitialInit);

#pragma endregion UAbilitySystemGlobals
};
