// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Animation/NEB_AnimInstance.h"

// Project Includes
#include "Characters/NEB_Character.h"

//----------------------------------------------------------------------------------------------------------------------
UNEB_AnimInstance::UNEB_AnimInstance()
{
	OwningCharacterVelocity = FVector();
	OwningCharacterSpeed = 0.f;
	MovementSpeedThreshold = 50.f; 
	bShouldMove = false;
	bIsFalling = false;
	bHasWeaponEquipped = false;
}

//----------------------------------------------------------------------------------------------------------------------
void UNEB_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	OwningCharacter = Cast<ANEB_Character>(TryGetPawnOwner());
	if(!OwningCharacter)
	{
		return;
	}

	OwningCharacterVelocity = OwningCharacter->GetVelocity();
	OwningCharacterSpeed = OwningCharacterVelocity.Size();
	bShouldMove = OwningCharacterSpeed > MovementSpeedThreshold;
}
