// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

// Framework Includes
#include "ActiveGameplayEffectHandle.h"
#include "GameplayTagContainer.h"
#include "Definitions/NEB_GameplayAbilitiesDefinitions.h"

// Generated Header Included Last
#include "NEB_GameplayStatics.generated.h"

class UNEB_GameplayEffect;
class UNEB_AbilitySystemComponent;

/**
 * Generic class that holds static functions that can be used anywhere in the project
 */
UCLASS()
class NEBULA_API UNEB_GameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#pragma region GameplayAbilitySystem

public:
	/**
	 * Applies a basic Gameplay Effect class to Target Ability System Component with SourceASC avatar as source object
	 * @param SourceAbilitySystemComponent Ability System Component that will apply the Gameplay Effect
	 * @param TargetAbilitySystemComponent Ability System Component that will receive the Gameplay Effect
	 * @param EffectClass Gameplay Effect Class to apply
	 * @param EffectLevel Value to define gameplay effect level for stats (1.f by default)
	 * @returns FActiveGameplayEffectHandle of gameplay effect applied
	 */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Ability System")
	static FActiveGameplayEffectHandle ApplyGameplayEffectToTarget( UNEB_AbilitySystemComponent* SourceAbilitySystemComponent, UNEB_AbilitySystemComponent* TargetAbilitySystemComponent, const TSubclassOf<UNEB_GameplayEffect>& EffectClass, const int32 EffectLevel = 1);

	/**
	 * Applies a Gameplay Effect Setup to Target Ability System Component with SourceASC avatar as source object
	 * @param SourceAbilitySystemComponent Ability System Component that will apply the Gameplay Effect
	 * @param TargetAbilitySystemComponent Ability System Component that will receive the Gameplay Effect
	 * @param EffectToApply Gameplay Effect Setup that holds the information to apply
	 * @returns FActiveGameplayEffectHandle of gameplay effect applied
	 */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Ability System")
	static FActiveGameplayEffectHandle ApplyGameplayEffectSetupToTarget( UNEB_AbilitySystemComponent* SourceAbilitySystemComponent, UNEB_AbilitySystemComponent* TargetAbilitySystemComponent, const FNEB_GameplayEffectSetup& EffectToApply);

	/**
	 * Applies a Gameplay Effect Setup to Target Ability System Component with custom source object, instigator and effectCauser
	 * @param SourceAbilitySystemComponent Ability System Component that will apply the Gameplay Effect
	 * @param TargetAbilitySystemComponent Ability System Component that will receive the Gameplay Effect
	 * @param EffectToApply Gameplay Effect Setup that holds the information to apply
	 * @param SourceObject Custom source object to register in context handle (SourceASC avatar if nullptr)
	 * @param Instigator Custom instigator of this effect to register in context handle (ignored if nullptr)
	 * @param EffectCauser Custom effect causer to register in context handle (ignored if nullptr)
	 * @returns FActiveGameplayEffectHandle of gameplay effect applied
	 */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Ability System")
	static FActiveGameplayEffectHandle ApplyCustomGameplayEffectSetupToTarget(UNEB_AbilitySystemComponent* SourceAbilitySystemComponent, UNEB_AbilitySystemComponent* TargetAbilitySystemComponent, const FNEB_GameplayEffectSetup& EffectToApply, const UObject* SourceObject, AActor* Instigator, AActor* EffectCauser);

	/**
	 * Returns true if the gameplay tag count is greater than zero
	 * @param AbilitySystemComponent Ability System Component in which tag is going to be search
	 * @param Tag Gameplay Tag that will be search in AbilitySystemComponent param
	 */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Ability System")
	static bool HasGameplayTag(const UNEB_AbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& Tag);

	/**
	 * Returns true if the gameplay tag count is greater than zero for any of the contained tags
	 * @param AbilitySystemComponent Ability System Component in which tags are going to be search
	 * @param TagList Gameplay Tag Container is the list of tags that will be search in AbilitySystemComponent param
	 */
	UFUNCTION(BlueprintCallable, Category = "Gameplay Ability System")
	static bool HasAnyGameplayTags(const UNEB_AbilitySystemComponent* AbilitySystemComponent, const FGameplayTagContainer& TagList);

	/**
	 * Initializes the attributes of the referred actor at a certain level
	 * @param ActorToInitialize Actor which attributes will be initialized
	 * @param Level Level at which the attributes should be initialized
	 */
	static void InitializeGameplayAttributes(AActor* ActorToInitialize, const int32 Level);

#pragma endregion GameplayAbilitySystem
};
