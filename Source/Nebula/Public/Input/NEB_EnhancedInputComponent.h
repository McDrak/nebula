// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "NEB_AbilityInputConfig.h"
#include "NEB_EnhancedInputComponent.generated.h"

/**
 * Enhanced Input Component for the Nebula Project
 */
UCLASS()
class NEBULA_API UNEB_EnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UNEB_EnhancedInputComponent();

#pragma region Ability System Inputs

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UNEB_AbilityInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);

#pragma endregion Ability System Inputs
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UNEB_EnhancedInputComponent::BindAbilityActions(const UNEB_AbilityInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	if(!InputConfig)
	{
		return;
	}

	for(const FNEB_AbilityInputConfigDefinition& CurrentDefinition : InputConfig->GetAbilityInputConfigDefinitions())
	{
		if(!CurrentDefinition.AbilityInputAction || !CurrentDefinition.AbilityInputTag.IsValid())
		{
			continue;
		}

		if(PressedFunc)
		{
			BindAction(CurrentDefinition.AbilityInputAction, ETriggerEvent::Triggered, Object, PressedFunc, CurrentDefinition.AbilityInputTag);
		}

		if(ReleasedFunc)
		{
			BindAction(CurrentDefinition.AbilityInputAction, ETriggerEvent::Completed, Object, ReleasedFunc, CurrentDefinition.AbilityInputTag);
		}

		if(HeldFunc)
		{
			BindAction(CurrentDefinition.AbilityInputAction, ETriggerEvent::Triggered, Object, HeldFunc, CurrentDefinition.AbilityInputTag);
		}
	}
}
