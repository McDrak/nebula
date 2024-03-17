// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

// Generated Header Included Last
#include "NEB_AnimInstance.generated.h"

class UNEB_CharacterMovementComponent;
class ANEB_Character;

/**
 * TODO
 */
UCLASS()
class NEBULA_API UNEB_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UNEB_AnimInstance();

#pragma region Core Properties

protected:
	UPROPERTY(Transient, BlueprintReadOnly,  Category = "Core Properties")
	TObjectPtr<ANEB_Character> OwningCharacter;

	UPROPERTY(Transient, BlueprintReadOnly,  Category = "Core Properties")
	TObjectPtr<UNEB_CharacterMovementComponent> OwningCharacterMovementComponent;

#pragma endregion Core Properties

#pragma region State Properties

protected:
	UPROPERTY(BlueprintReadOnly,  Category = "State Properties")
	FVector OwningCharacterVelocity;

	UPROPERTY(BlueprintReadOnly,  Category = "State Properties")
	float OwningCharacterGroundSpeed;

	UPROPERTY(BlueprintReadOnly,  Category = "State Properties")
	uint8 bShouldMove : 1;

	UPROPERTY(BlueprintReadOnly,  Category = "State Properties")
	uint8 bIsFalling : 1;

	UPROPERTY(BlueprintReadOnly,  Category = "State Properties")
	uint8 bHasWeaponEquipped : 1;

#pragma endregion State Properties

};
