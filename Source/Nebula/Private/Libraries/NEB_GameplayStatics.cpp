// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Libraries/NEB_GameplayStatics.h"

// Framework Includes
#include "ActiveGameplayEffectHandle.h"

// Project Includes
#include "GameplayAbilitySystem/NEB_AbilitySystemComponent.h"
#include "GameplayAbilitySystem/NEB_GameplayEffect.h"

//----------------------------------------------------------------------------------------------------------------------
FActiveGameplayEffectHandle UNEB_GameplayStatics::ApplyGameplayEffectToTarget(UNEB_AbilitySystemComponent* SourceAbilitySystemComponent, UNEB_AbilitySystemComponent* TargetAbilitySystemComponent, const TSubclassOf<UNEB_GameplayEffect>& EffectClass, const int32 EffectLevel)
{
	if(!IsValid(EffectClass))
	{
		return FActiveGameplayEffectHandle();
	}

	FNEB_GameplayEffectSetup GameplayEffectSetup;
	GameplayEffectSetup.GameplayEffectClass = EffectClass;
	GameplayEffectSetup.EffectLevelMagnitude = EffectLevel > 0 ? EffectLevel : 1;
	return ApplyCustomGameplayEffectSetupToTarget(SourceAbilitySystemComponent, TargetAbilitySystemComponent, GameplayEffectSetup, nullptr, nullptr, nullptr);
}

//----------------------------------------------------------------------------------------------------------------------
FActiveGameplayEffectHandle UNEB_GameplayStatics::ApplyGameplayEffectSetupToTarget(UNEB_AbilitySystemComponent* SourceAbilitySystemComponent, UNEB_AbilitySystemComponent* TargetAbilitySystemComponent, const FNEB_GameplayEffectSetup& EffectToApply)
{
	return ApplyCustomGameplayEffectSetupToTarget(SourceAbilitySystemComponent, TargetAbilitySystemComponent, EffectToApply, nullptr, nullptr, nullptr);
}

//----------------------------------------------------------------------------------------------------------------------
FActiveGameplayEffectHandle UNEB_GameplayStatics::ApplyCustomGameplayEffectSetupToTarget(UNEB_AbilitySystemComponent* SourceAbilitySystemComponent, UNEB_AbilitySystemComponent* TargetAbilitySystemComponent, const FNEB_GameplayEffectSetup& EffectToApply, const UObject* SourceObject, AActor* Instigator, AActor* EffectCauser)
{
	if(!IsValid(SourceAbilitySystemComponent) || !IsValid(TargetAbilitySystemComponent) || !IsValid(EffectToApply.GameplayEffectClass))
	{
		return FActiveGameplayEffectHandle();
	}

	FGameplayEffectContextHandle EffectContextHandle = SourceAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(IsValid(SourceObject)? SourceObject : SourceAbilitySystemComponent->GetAvatarActor());
	
	if(IsValid(Instigator) || IsValid(EffectCauser))
	{
		EffectContextHandle.AddInstigator(Instigator, EffectCauser);
	}

	const FGameplayEffectSpecHandle& EffectSpecHandle = SourceAbilitySystemComponent->MakeOutgoingSpec(EffectToApply.GameplayEffectClass, EffectToApply.EffectLevelMagnitude, EffectContextHandle);
	if (!EffectSpecHandle.IsValid())
	{
		return FActiveGameplayEffectHandle();
	}

	if(EffectToApply.SetByCallerTag.IsValid())
	{
		if(EffectToApply.bUseAttributeMagnitude)
		{
			const float AttributeMagnitude = SourceAbilitySystemComponent->GetNumericAttribute(EffectToApply.BackingAttribute);
			EffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(EffectToApply.SetByCallerTag, AttributeMagnitude);
		}
		else
		{
			EffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(EffectToApply.SetByCallerTag, EffectToApply.SetByCallerMagnitude);
		}
	}

	if(EffectToApply.bShouldModifyDuration)
	{
		if(EffectToApply.SetByCallerDurationTag.IsValid())
		{
			EffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(EffectToApply.SetByCallerDurationTag, EffectToApply.DurationMagnitude);
		}
		else
		{
			EffectSpecHandle.Data.Get()->SetDuration(EffectToApply.DurationMagnitude, true);
		}
	}

	if(EffectToApply.DynamicGrantedTags.Num() > 0)
	{
		EffectSpecHandle.Data.Get()->DynamicGrantedTags = EffectToApply.DynamicGrantedTags;
	}

	return SourceAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetAbilitySystemComponent);
}

//----------------------------------------------------------------------------------------------------------------------
bool UNEB_GameplayStatics::HasGameplayTag(const UNEB_AbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& Tag)
{
	if (!Tag.IsValid())
	{
		return false;
	}

	if (IsValid(AbilitySystemComponent))
	{
		return AbilitySystemComponent->HasMatchingGameplayTag(Tag);
	}

	return false;
}

//----------------------------------------------------------------------------------------------------------------------
bool UNEB_GameplayStatics::HasAnyGameplayTags(const UNEB_AbilitySystemComponent* AbilitySystemComponent, const FGameplayTagContainer& TagList)
{
	if (IsValid(AbilitySystemComponent))
	{
		return AbilitySystemComponent->HasAnyMatchingGameplayTags(TagList);
	}

	return false;
}
