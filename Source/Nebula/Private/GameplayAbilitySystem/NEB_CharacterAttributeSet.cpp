// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "GameplayAbilitySystem/NEB_CharacterAttributeSet.h"

// Engine Includes
#include "Net/UnrealNetwork.h"

// Framework Includes
#include "GameplayEffectExtension.h"

//----------------------------------------------------------------------------------------------------------------------
UNEB_CharacterAttributeSet::UNEB_CharacterAttributeSet()
{
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_CharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 100.0f);
		Health = FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue());
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_CharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_CharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UNEB_CharacterAttributeSet, Health, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UNEB_CharacterAttributeSet, MaxHealth, COND_OwnerOnly, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UNEB_CharacterAttributeSet, WalkingSpeed, COND_InitialOnly, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UNEB_CharacterAttributeSet, SprintingSpeed, COND_InitialOnly, REPNOTIFY_OnChanged);
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_CharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNEB_CharacterAttributeSet, Health, OldHealth);
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_CharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNEB_CharacterAttributeSet, MaxHealth, OldMaxHealth);
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_CharacterAttributeSet::OnRep_WalkingSpeed(const FGameplayAttributeData& OldWalkingSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNEB_CharacterAttributeSet, WalkingSpeed, OldWalkingSpeed);
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_CharacterAttributeSet::OnRep_SprintingSpeed(const FGameplayAttributeData& OldSprintingSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNEB_CharacterAttributeSet, SprintingSpeed, OldSprintingSpeed);
}
