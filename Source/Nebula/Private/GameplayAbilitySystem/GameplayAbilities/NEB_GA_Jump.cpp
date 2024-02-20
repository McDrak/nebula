// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "GameplayAbilitySystem/GameplayAbilities/NEB_GA_Jump.h"

// Project Includes
#include "Characters/NEB_Character.h"

//----------------------------------------------------------------------------------------------------------------------
UNEB_GA_Jump::UNEB_GA_Jump()
{
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_GA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if(ANEB_Character* AvatarCharacter = Cast<ANEB_Character>(GetAvatarActorFromActorInfo()))
	{
		AvatarCharacter->Jump();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_GA_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(ANEB_Character* AvatarCharacter = Cast<ANEB_Character>(GetAvatarActorFromActorInfo()))
	{
		AvatarCharacter->StopJumping();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_GA_Jump::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
