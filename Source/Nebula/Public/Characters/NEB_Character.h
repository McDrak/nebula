// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Framework Includes
#include "AbilitySystemInterface.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"

// Project Includes
#include "Definitions/NEB_GameplayAbilitiesDefinitions.h"

// Generated Header Included Last
#include "NEB_Character.generated.h"

class UNEB_GameplayAbility;
class UNEB_CharacterAttributeSet;
class UNEB_AbilitySystemComponent;

/**
 * Base class for the Characters in the Nebula Project
 */
UCLASS()
class NEBULA_API ANEB_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ANEB_Character();

#pragma region AActor

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

#pragma endregion AActor

#pragma region IAbilitySystemInterface

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

#pragma endregion IAbilitySystemInterface

#pragma region Components

protected:
	UPROPERTY()
	TObjectPtr<UNEB_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UNEB_CharacterAttributeSet> AttributeSet;

#pragma endregion Components

#pragma region GameplayAbilitySystem

protected:
	/** Attributes Effect that will be applied to the Character when the game starts */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability System")
	FNEB_GameplayEffectSetup InitialAttributesSetup;

	/** Gameplay Abilities (such as Sprint, Jump, etc) to be granted to the Character when the game starts */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability System")
	TArray<TSubclassOf<UNEB_GameplayAbility>> InitialCharacterAbilities;

	/** Gameplay Effects (such as Stamina Regen, Health Regen, etc) to be applied to the Character when the game starts */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability System")
	TArray<FNEB_GameplayEffectSetup> StartupCharacterEffects;

	/**
	 * Map that holds which Gameplay Effects has been applied and their corresponding handles.
	 * This simplifies the process of removing them.
	 */
	TMap<TSubclassOf<UNEB_GameplayEffect>, FActiveGameplayEffectHandle> AppliedEffectsMap;

	/**
	 * Map that holds which Gameplay Abilities has been granted and their corresponding handles.
	 * This simplifies the process of (de)activating them
	 */
	TMap<TSubclassOf<UNEB_GameplayAbility>, FGameplayAbilitySpecHandle> GrantedAbilitiesMap;

	void InitializeAttributes();

	void GrantInitialCharacterAbilities();

	void ApplyStartupCharacterEffects();

public:
	UNEB_CharacterAttributeSet* GetNEBAttributeSet() const { return AttributeSet.Get(); }

#pragma endregion GameplayAbilitySystem

};
