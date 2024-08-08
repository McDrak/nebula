// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "GameFramework/NEB_GameInstance.h"

// Project Includes
#include "GameplayAbilitySystem/NEB_AbilitySystemGlobals.h"

//----------------------------------------------------------------------------------------------------------------------
UNEB_GameInstance::UNEB_GameInstance()
{
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_GameInstance::Init()
{
	Super::Init();

	if(UNEB_AbilitySystemGlobals* AbilitySystemGlobals = Cast<UNEB_AbilitySystemGlobals>(IGameplayAbilitiesModule::Get().GetAbilitySystemGlobals()))
	{
		AbilitySystemGlobals->ReloadAttributeDefaults();
	}
}
