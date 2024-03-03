// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Input/NEB_EnhancedInputComponent.h"

//----------------------------------------------------------------------------------------------------------------------
UNEB_EnhancedInputComponent::UNEB_EnhancedInputComponent()
{
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_EnhancedInputComponent::UnBindAbilityActions(const UNEB_AbilityInputConfig* InputConfig)
{
	if(!InputConfig)
	{
		return;
	}

	for(const FNEB_AbilityInputConfigDefinition& CurrentConfigDefinition : InputConfig->GetAbilityInputConfigDefinitions())
	{
		if(!CurrentConfigDefinition.AbilityInputAction || !AbilityInputBindsMap.Contains(CurrentConfigDefinition.AbilityInputAction.Get()))
		{
			continue;
		}

		const FNEB_AbilityInputBindDefinition CurrentBindDefinition = AbilityInputBindsMap[CurrentConfigDefinition.AbilityInputAction.Get()];
		if(CurrentBindDefinition.InputPressedBind)
		{
			RemoveBinding(*CurrentBindDefinition.InputPressedBind);
		}

		if(CurrentBindDefinition.InputReleasedBind)
		{
			RemoveBinding(*CurrentBindDefinition.InputReleasedBind);
		}

		if(CurrentBindDefinition.InputHeldBind)
		{
			RemoveBinding(*CurrentBindDefinition.InputHeldBind);
		}

		AbilityInputBindsMap.Remove(CurrentConfigDefinition.AbilityInputAction.Get());
	}
}
