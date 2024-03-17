// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"

// Generated Header Included Last
#include "NEB_CharacterMovementComponent.generated.h"

/**
 * TODO
 */
UCLASS()
class NEBULA_API UNEB_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UNEB_CharacterMovementComponent();

#pragma region UMovementComponent

public:
	virtual float GetMaxSpeed() const override;

#pragma endregion UMovementComponent

};
