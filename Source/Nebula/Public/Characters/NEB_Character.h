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
class ANEB_Item;

/**
 * Base class for the Characters in the Nebula Project
 */
UCLASS()
class NEBULA_API ANEB_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ANEB_Character(const FObjectInitializer& ObjectInitializer);

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UNEB_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UNEB_CharacterAttributeSet> CharacterAttributeSet;

#pragma endregion Components

#pragma region GameplayAbilitySystem

protected:
	/** Gameplay Abilities (such as Sprint, Jump, etc.) to be granted to the Character when the game starts */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability System")
	TArray<TSubclassOf<UNEB_GameplayAbility>> InitialCharacterAbilities;

	/** Gameplay Effects (such as Stamina Regen, Health Regen, etc.) to be applied to the Character when the game starts */
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
	void GiveAbilities(const TArray<TSubclassOf<UNEB_GameplayAbility>>& AbilitiesToGive);
	void RemoveAbilities(const TArray<TSubclassOf<UNEB_GameplayAbility>>& AbilitiesToRemove);

	UNEB_CharacterAttributeSet* GetNEBAttributeSet() const { return CharacterAttributeSet.Get(); }

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

#pragma endregion GameplayAbilitySystem

#pragma region Pick Up

protected:
	TWeakObjectPtr<ANEB_Item> CurrentHoldingItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pick Up")
	FName EquipSocketName;

public:
	FName GetEquipSocketName() const { return EquipSocketName; }

	void EquipItem(ANEB_Item* ItemToEquip);

#pragma endregion Pick Up

};
