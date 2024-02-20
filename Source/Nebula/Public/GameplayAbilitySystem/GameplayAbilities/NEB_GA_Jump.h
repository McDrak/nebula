// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Project Includes
#include "GameplayAbilitySystem/NEB_GameplayAbility.h"

// Generated Header Included Last
#include "NEB_GA_Jump.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API UNEB_GA_Jump : public UNEB_GameplayAbility
{
	GENERATED_BODY()

public:
	UNEB_GA_Jump();

#pragma region UGameplayAbility

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

#pragma endregion UGameplayAbility
};
