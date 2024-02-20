// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Input/NEB_AbilityInputConfig.h"

//----------------------------------------------------------------------------------------------------------------------
UNEB_AbilityInputConfig::UNEB_AbilityInputConfig()
{
}

//----------------------------------------------------------------------------------------------------------------------
UInputAction* UNEB_AbilityInputConfig::GetInputActionFromGameplayTag(const FGameplayTag& AbilityInputTag) const
{
	const int32 AbilityInputActionIndex = AbilityInputConfig.IndexOfByPredicate([AbilityInputTag](const FNEB_AbilityInputConfigDefinition& CurrentInputConfig)
	{
		return CurrentInputConfig.AbilityInputAction && CurrentInputConfig.AbilityInputTag == AbilityInputTag;
	});

	if(AbilityInputActionIndex == INDEX_NONE)
	{
		return nullptr;
	}

	return AbilityInputConfig[AbilityInputActionIndex].AbilityInputAction.Get();
}
