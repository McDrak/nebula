// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Characters/NEB_AICharacter.h"

// Project Includes
#include "Definitions/NEB_AIDefinitions.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_AICharacter::ANEB_AICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentAIState = ENEB_AIState::Patrolling;
	CurrentSplinePathPoint = -1;
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_AICharacter::BP_SetAIState_Implementation(const ENEB_AIState NewAIState)
{
	if(CurrentAIState != NewAIState)
	{
		CurrentAIState = NewAIState;
	}
}
