// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "GameplayAbilitySystem/NEB_AbilitySystemComponent.h"

//----------------------------------------------------------------------------------------------------------------------
UNEB_AbilitySystemComponent::UNEB_AbilitySystemComponent()
{
	bWereInitialAbilitiesGranted = false;
	bWereStartupEffectsApplied = false;
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_AbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& AbilityInputTag)
{
	if(!AbilityInputTag.IsValid())
	{
		return;
	}

	for(FGameplayAbilitySpec CurrentAbilitySpec : GetActivatableAbilities())
	{
		if(!CurrentAbilitySpec.DynamicAbilityTags.HasTagExact(AbilityInputTag))
		{
			continue;
		}

		AbilitySpecInputPressed(CurrentAbilitySpec);
		if(!CurrentAbilitySpec.IsActive())
		{
			TryActivateAbility(CurrentAbilitySpec.Handle);
		}
		break;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_AbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& AbilityInputTag)
{
	if(!AbilityInputTag.IsValid())
	{
		return;
	}

	for(FGameplayAbilitySpec CurrentAbilitySpec : GetActivatableAbilities())
	{
		if(!CurrentAbilitySpec.DynamicAbilityTags.HasTagExact(AbilityInputTag))
		{
			continue;
		}

		AbilitySpecInputReleased(CurrentAbilitySpec);
		break;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_AbilitySystemComponent::OnAbilityInputHeld(const FGameplayTag& AbilityInputTag)
{
	if(!AbilityInputTag.IsValid())
	{
		return;
	}

	for(FGameplayAbilitySpec CurrentAbilitySpec : GetActivatableAbilities())
	{
		if(!CurrentAbilitySpec.DynamicAbilityTags.HasTagExact(AbilityInputTag))
		{
			continue;
		}

		if(!CurrentAbilitySpec.IsActive())
		{
			TryActivateAbility(CurrentAbilitySpec.Handle);
		}
		break;
	}
}
