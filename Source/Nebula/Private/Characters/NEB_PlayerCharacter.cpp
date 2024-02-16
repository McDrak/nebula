// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Characters/NEB_PlayerCharacter.h"

// Project Includes
#include "GameFramework/NEB_PlayerState.h"
#include "GameplayAbilitySystem/NEB_AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/NEB_PlayerAttributeSet.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_PlayerCharacter::ANEB_PlayerCharacter()
{
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(ANEB_PlayerState* CurrentPlayerState = GetPlayerState<ANEB_PlayerState>())
	{
		AbilitySystemComponent = Cast<UNEB_AbilitySystemComponent>(CurrentPlayerState->GetAbilitySystemComponent());
		AttributeSet = CurrentPlayerState->GetNEBAttributeSet();

		CurrentPlayerState->InitAbilityActorInfo(this);

		InitializeAttributes();
		GrantInitialCharacterAbilities();
		ApplyStartupCharacterEffects();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if(ANEB_PlayerState* CurrentPlayerState = GetPlayerState<ANEB_PlayerState>())
	{
		AbilitySystemComponent = Cast<UNEB_AbilitySystemComponent>(CurrentPlayerState->GetAbilitySystemComponent());
		AttributeSet = CurrentPlayerState->GetNEBAttributeSet();

		CurrentPlayerState->InitAbilityActorInfo(this);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
