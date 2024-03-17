// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Characters/NEB_Character.h"

// Project Includes
#include "Actors/NEB_Item.h"
#include "Components/NEB_CharacterMovementComponent.h"
#include "GameplayAbilitySystem/NEB_AbilitySystemComponent.h"
#include "GameplayAbilitySystem/NEB_GameplayAbility.h"
#include "GameplayAbilitySystem/NEB_GameplayEffect.h"
#include "Libraries/NEB_GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_Character::ANEB_Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UNEB_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Character::BeginPlay()
{
	Super::BeginPlay();
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent* ANEB_Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Character::InitializeAttributes()
{
	if(!HasAuthority() || !InitialAttributesSetup.GameplayEffectClass || !AbilitySystemComponent)
	{
		return;
	}

	UNEB_GameplayStatics::ApplyGameplayEffectSetupToTarget(AbilitySystemComponent.Get(), AbilitySystemComponent.Get(), InitialAttributesSetup);
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Character::GrantInitialCharacterAbilities()
{
	if(!HasAuthority() || !AbilitySystemComponent || AbilitySystemComponent->WereInitialAbilitiesGranted())
	{
		return;
	}

	GiveAbilities(InitialCharacterAbilities);
	AbilitySystemComponent->SetInitialAbilitiesGranted(true);
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Character::ApplyStartupCharacterEffects()
{
	if(!HasAuthority() || !AbilitySystemComponent || AbilitySystemComponent->WereStartupEffectsApplied())
	{
		return;
	}

	for(const FNEB_GameplayEffectSetup& CurrentEffectSetup : StartupCharacterEffects)
	{
		if(!CurrentEffectSetup.GameplayEffectClass)
		{
			continue;
		}

		FActiveGameplayEffectHandle CurrentEffectHandle = UNEB_GameplayStatics::ApplyGameplayEffectSetupToTarget(AbilitySystemComponent.Get(), AbilitySystemComponent.Get(), CurrentEffectSetup);
		if(!CurrentEffectHandle.IsValid())
		{
			continue;
		}

		AppliedEffectsMap.Add(CurrentEffectSetup.GameplayEffectClass, CurrentEffectHandle);
	}

	AbilitySystemComponent->SetStartupEffectsApplied(true);
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Character::GiveAbilities(const TArray<TSubclassOf<UNEB_GameplayAbility>>& AbilitiesToGive)
{
	if(!HasAuthority() || !AbilitySystemComponent)
	{
		return;
	}

	for(TSubclassOf<UNEB_GameplayAbility> CurrentAbilityClass : InitialCharacterAbilities)
	{
		FGameplayAbilitySpec CurrentAbilitySpec(CurrentAbilityClass, 1);
		if(const UNEB_GameplayAbility* CurrentAbility  = Cast<UNEB_GameplayAbility>(CurrentAbilitySpec.Ability))
		{
			CurrentAbilitySpec.DynamicAbilityTags.AddTag(CurrentAbility->GetStartupInputTag());
			CurrentAbilitySpec.SourceObject = this;

			FGameplayAbilitySpecHandle CurrentAbilityHandle = AbilitySystemComponent->GiveAbility(CurrentAbilitySpec);
			if(!CurrentAbilityHandle.IsValid())
			{
				continue;
			}

			GrantedAbilitiesMap.Add(CurrentAbilityClass, CurrentAbilityHandle);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Character::RemoveAbilities(const TArray<TSubclassOf<UNEB_GameplayAbility>>& AbilitiesToRemove)
{
	if(!HasAuthority() || !AbilitySystemComponent)
	{
		return;
	}

	for(const TSubclassOf<UNEB_GameplayAbility>& CurrentAbilityClass : AbilitiesToRemove)
	{
		if(GrantedAbilitiesMap.Contains(CurrentAbilityClass))
		{
			AbilitySystemComponent->ClearAbility(GrantedAbilitiesMap[CurrentAbilityClass]);
			GrantedAbilitiesMap.Remove(CurrentAbilityClass);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Character::EquipItem(ANEB_Item* ItemToEquip)
{
	if(!ItemToEquip)
	{
		return;
	}

	if(CurrentHoldingItem.IsValid())
	{
		CurrentHoldingItem->OnItemDropped();
		CurrentHoldingItem = nullptr;
	}

	CurrentHoldingItem->OnItemPickedUp(this);
}

