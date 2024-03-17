// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Animation/NEB_AnimInstance.h"

//----------------------------------------------------------------------------------------------------------------------
UNEB_AnimInstance::UNEB_AnimInstance()
{
	OwningCharacterVelocity = FVector();
	OwningCharacterGroundSpeed = 0.f;
	bShouldMove = false;
	bIsFalling = false;
	bHasWeaponEquipped = false;
}
