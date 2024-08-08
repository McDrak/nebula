// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "GameFramework/NEB_PlayerState.h"

// Project Includes
#include "GameplayAbilitySystem/NEB_AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/NEB_PlayerAttributeSet.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_PlayerState::ANEB_PlayerState()
{
	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UNEB_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	// Mixed mode means we only are replicated the GEs to ourselves, not the GEs to simulated proxies.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	PlayerAttributeSet = CreateDefaultSubobject<UNEB_PlayerAttributeSet>(TEXT("PlayerAttributeSet"));

	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	NetUpdateFrequency = 30.f;
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerState::BeginPlay()
{
	Super::BeginPlay();
}

//----------------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent* ANEB_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerState::InitAbilityActorInfo(APawn* InAvatarActor)
{
	if(AbilitySystemComponent && InAvatarActor)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, InAvatarActor);
	}
}
