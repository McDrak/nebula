// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Project Includes
#include "Actors/NEB_Item.h"

// Generated Header Included Last
#include "NEB_Weapon.generated.h"

class UNEB_GameplayAbility;
class UNEB_AbilityInputConfig;
class UInputMappingContext;
class UNEB_WeaponAttributeSet;

/**
 * TODO
 */
UCLASS()
class NEBULA_API ANEB_Weapon : public ANEB_Item
{
	GENERATED_BODY()

public:
	ANEB_Weapon();

#pragma region ANEB_Item

public:
	virtual void OnItemPickedUp(ANEB_Character* EquippingCharacter) override;
	virtual void OnItemDropped() override;

#pragma endregion ANEB_Item

#pragma region Components

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UNEB_WeaponAttributeSet> AttributeSet;

#pragma endregion Components

#pragma region Inputs

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UInputMappingContext> WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UNEB_AbilityInputConfig> WeaponAbilityInputs;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TArray<TSubclassOf<UNEB_GameplayAbility>> WeaponAbilitiesToGive;

#pragma endregion Inputs

};
