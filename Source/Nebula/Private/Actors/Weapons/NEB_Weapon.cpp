// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Actors/Weapons/NEB_Weapon.h"

// Project Includes
#include "Characters/NEB_Character.h"
#include "Characters/NEB_PlayerCharacter.h"
#include "GameFramework/NEB_PlayerController.h"
#include "GameplayAbilitySystem/AttributeSets/NEB_WeaponAttributeSet.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_Weapon::ANEB_Weapon()
{
	AttributeSet = CreateDefaultSubobject<UNEB_WeaponAttributeSet>(TEXT("AttributeSet"));
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Weapon::OnItemPickedUp(ANEB_Character* EquippingCharacter)
{
	Super::OnItemPickedUp(EquippingCharacter);

	if(!EquippingCharacter)
	{
		return;
	}

	EquippingCharacter->GiveAbilities(WeaponAbilitiesToGive);
	if(ANEB_PlayerCharacter* EquippingPlayerCharacter = Cast<ANEB_PlayerCharacter>(EquippingCharacter))
	{
		EquippingPlayerCharacter->AddInputMappingContext(WeaponInputMappingContext.Get());

		if(ANEB_PlayerController* EquippingPlayerController = EquippingPlayerCharacter->GetNEBPlayerController())
		{
			EquippingPlayerController->BindAbilityInputConfig(WeaponAbilityInputs.Get());
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Weapon::OnItemDropped()
{
	Super::OnItemDropped();

	if(!PreviousHolderCharacterPtr.IsValid())
	{
		return;
	}

	PreviousHolderCharacterPtr->RemoveAbilities(WeaponAbilitiesToGive);
	if(ANEB_PlayerCharacter* PreviousHolderPlayerCharacter = Cast<ANEB_PlayerCharacter>(PreviousHolderCharacterPtr))
	{
		PreviousHolderPlayerCharacter->RemoveInputMappingContext(WeaponInputMappingContext.Get());

		if(ANEB_PlayerController* PreviousHolderPlayerController = PreviousHolderPlayerCharacter->GetNEBPlayerController())
		{
			PreviousHolderPlayerController->UnBindAbilityInputConfig(WeaponAbilityInputs.Get());
		}
	}
}
