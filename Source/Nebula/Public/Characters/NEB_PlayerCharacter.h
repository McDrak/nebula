// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Project Includes
#include "Characters/NEB_Character.h"

// Generated Header Included Last
#include "NEB_PlayerCharacter.generated.h"

/**
 * Character for Players on the Nebula Project
 */
UCLASS()
class NEBULA_API ANEB_PlayerCharacter : public ANEB_Character
{
	GENERATED_BODY()

public:
	ANEB_PlayerCharacter();

#pragma region AActor

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

#pragma endregion AActor

#pragma region APawn

public:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

#pragma endregion APawn

};
