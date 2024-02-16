// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "GameFramework/NEB_PlayerController.h"

// Project Includes
#include "Characters/NEB_PlayerCharacter.h"
#include "GameFramework/NEB_PlayerState.h"

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
}
