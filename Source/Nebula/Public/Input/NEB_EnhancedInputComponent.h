// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"

// Project Includes
#include "NEB_AbilityInputConfig.h"

// Generated Header Included Last
#include "NEB_EnhancedInputComponent.generated.h"

/**
 * TODO
 */
USTRUCT()
struct FNEB_AbilityInputBindDefinition
{
	GENERATED_BODY()

	FEnhancedInputActionEventBinding* InputPressedBind;

	FEnhancedInputActionEventBinding* InputReleasedBind;

	FEnhancedInputActionEventBinding* InputHeldBind;

	FNEB_AbilityInputBindDefinition()
		: InputPressedBind(nullptr), InputReleasedBind(nullptr), InputHeldBind(nullptr)
	{
	}
};

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

protected:
	UPROPERTY(Transient)
	TMap<UInputAction*, FNEB_AbilityInputBindDefinition> AbilityInputBindsMap; 

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UNEB_AbilityInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);

	void UnBindAbilityActions(const UNEB_AbilityInputConfig* InputConfig);

#pragma endregion Ability System Inputs
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UNEB_EnhancedInputComponent::BindAbilityActions(const UNEB_AbilityInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	if(!InputConfig)
	{
		return;
	}

	for(const FNEB_AbilityInputConfigDefinition& CurrentConfigDefinition : InputConfig->GetAbilityInputConfigDefinitions())
	{
		if(!CurrentConfigDefinition.AbilityInputAction || !CurrentConfigDefinition.AbilityInputTag.IsValid())
		{
			continue;
		}

		FNEB_AbilityInputBindDefinition InputBindDefinition;

		if(PressedFunc)
		{
			FEnhancedInputActionEventBinding& PressedInputBind = BindAction(CurrentConfigDefinition.AbilityInputAction, ETriggerEvent::Triggered, Object, PressedFunc, CurrentConfigDefinition.AbilityInputTag);
			InputBindDefinition.InputPressedBind = &PressedInputBind;
		}

		if(ReleasedFunc)
		{
			FEnhancedInputActionEventBinding& ReleasedInputBind = BindAction(CurrentConfigDefinition.AbilityInputAction, ETriggerEvent::Completed, Object, ReleasedFunc, CurrentConfigDefinition.AbilityInputTag);
			InputBindDefinition.InputReleasedBind = &ReleasedInputBind;
		}

		if(HeldFunc)
		{
			FEnhancedInputActionEventBinding& HeldInputBind = BindAction(CurrentConfigDefinition.AbilityInputAction, ETriggerEvent::Triggered, Object, HeldFunc, CurrentConfigDefinition.AbilityInputTag);
			InputBindDefinition.InputHeldBind = &HeldInputBind;
		}

		AbilityInputBindsMap.Add(CurrentConfigDefinition.AbilityInputAction.Get(), InputBindDefinition);
	}
}
