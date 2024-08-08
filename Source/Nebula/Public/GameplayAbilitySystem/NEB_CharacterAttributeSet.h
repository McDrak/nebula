// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Framework Includes
#include "AttributeSet.h"

// Project Includes
#include "Definitions/NEB_GameplayAbilitiesDefinitions.h"

// Generated Header Included Last
#include "NEB_CharacterAttributeSet.generated.h"

/**
 * Base class for the Attribute Set in the Nebula Project 
 */
UCLASS()
class NEBULA_API UNEB_CharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UNEB_CharacterAttributeSet();

#pragma region UAttributeSet

public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

#pragma endregion UAttributeSet

#pragma region Attributes

public:
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_WalkingSpeed)
	FGameplayAttributeData WalkingSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_SprintingSpeed)
	FGameplayAttributeData SprintingSpeed;

	ATTRIBUTE_ACCESSORS(UNEB_CharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UNEB_CharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UNEB_CharacterAttributeSet, WalkingSpeed);
	ATTRIBUTE_ACCESSORS(UNEB_CharacterAttributeSet, SprintingSpeed);

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	void OnRep_WalkingSpeed(const FGameplayAttributeData& OldWalkingSpeed);

	UFUNCTION()
	void OnRep_SprintingSpeed(const FGameplayAttributeData& OldSprintingSpeed);

#pragma endregion Attributes

};
