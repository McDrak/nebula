// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Characters/NEB_Character.h"

// Project Includes
#include "GameplayAbilitySystem/NEB_AbilitySystemComponent.h"
#include "GameplayAbilitySystem/NEB_GameplayAbility.h"
#include "GameplayAbilitySystem/NEB_GameplayEffect.h"
#include "Libraries/NEB_GameplayStatics.h"

//----------------------------------------------------------------------------------------------------------------------
// Sets default values
ANEB_Character::ANEB_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

//----------------------------------------------------------------------------------------------------------------------
// Called when the game starts or when spawned
void ANEB_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

//----------------------------------------------------------------------------------------------------------------------
// Called every frame
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

