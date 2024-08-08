// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "GameplayAbilitySystem/NEB_AbilitySystemGlobals.h"

//----------------------------------------------------------------------------------------------------------------------
UNEB_AbilitySystemGlobals::UNEB_AbilitySystemGlobals()
{
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_AbilitySystemGlobals::ReloadAttributeDefaults()
{
	Super::ReloadAttributeDefaults();
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_AbilitySystemGlobals::InitAttributeDefaults(UAbilitySystemComponent* AbilitySystemComponent, const FName& GroupName, const int32 Level, const bool bInitialInit)
{
	if (FAttributeSetInitter* AttributeSetInitter = GetAttributeSetInitter())
	{
		AttributeSetInitter->InitAttributeSetDefaults(AbilitySystemComponent, GroupName, Level, bInitialInit);
	}
}
