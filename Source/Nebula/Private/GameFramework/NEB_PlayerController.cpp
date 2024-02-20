// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "GameFramework/NEB_PlayerController.h"

// Project Includes
#include "Characters/NEB_PlayerCharacter.h"
#include "GameFramework/NEB_PlayerState.h"
#include "GameplayAbilitySystem/NEB_AbilitySystemComponent.h"
#include "Input/NEB_EnhancedInputComponent.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_PlayerController::ANEB_PlayerController()
{
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(ANEB_PlayerCharacter* CurrentPlayerCharacter = Cast<ANEB_PlayerCharacter>(InPawn))
	{
		PlayerCharacterPtr = CurrentPlayerCharacter;
	}

	if(ANEB_PlayerState* CurrentPlayerState = GetPlayerState<ANEB_PlayerState>())
	{
		CurrentPlayerState->InitAbilityActorInfo(InPawn);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UNEB_EnhancedInputComponent* EnhancedInputComponent = Cast<UNEB_EnhancedInputComponent>(InputComponent); EnhancedInputComponent && AbilityInputConfig)
	{
		EnhancedInputComponent->BindAbilityActions(AbilityInputConfig.Get(), this, &ANEB_PlayerController::OnAbilityInputPressed, &ANEB_PlayerController::OnAbilityInputReleased, &ANEB_PlayerController::OnAbilityInputHeld);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerController::OnAbilityInputPressed(FGameplayTag AbilityInputTag)
{
	if(!PlayerCharacterPtr.IsValid() || !AbilityInputTag.IsValid())
	{
		return;
	}

	if(UNEB_AbilitySystemComponent* AbilitySystemComponent = Cast<UNEB_AbilitySystemComponent>(PlayerCharacterPtr->GetAbilitySystemComponent()))
	{
		AbilitySystemComponent->OnAbilityInputPressed(AbilityInputTag);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerController::OnAbilityInputReleased(FGameplayTag AbilityInputTag)
{
	if(!PlayerCharacterPtr.IsValid() || !AbilityInputTag.IsValid())
	{
		return;
	}

	if(UNEB_AbilitySystemComponent* AbilitySystemComponent = Cast<UNEB_AbilitySystemComponent>(PlayerCharacterPtr->GetAbilitySystemComponent()))
	{
		AbilitySystemComponent->OnAbilityInputReleased(AbilityInputTag);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerController::OnAbilityInputHeld(FGameplayTag AbilityInputTag)
{
	if(!PlayerCharacterPtr.IsValid() || !AbilityInputTag.IsValid())
	{
		return;
	}

	if(UNEB_AbilitySystemComponent* AbilitySystemComponent = Cast<UNEB_AbilitySystemComponent>(PlayerCharacterPtr->GetAbilitySystemComponent()))
	{
		AbilitySystemComponent->OnAbilityInputHeld(AbilityInputTag);
	}
}
