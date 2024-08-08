// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

// Framework Includes
#include "AbilitySystemInterface.h"

// Generated Header Included Last
#include "NEB_PlayerState.generated.h"

class UNEB_PlayerAttributeSet;
class UNEB_AbilitySystemComponent;

/**
 * Base Player State class for the Nebula Project
 */
UCLASS()
class NEBULA_API ANEB_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ANEB_PlayerState();

#pragma region AActor

protected:
	virtual void BeginPlay() override;

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
	TObjectPtr<UNEB_PlayerAttributeSet> PlayerAttributeSet;

#pragma endregion Components

#pragma region Gameplay Ability System

public:
	UNEB_PlayerAttributeSet* GetNEBAttributeSet() const { return PlayerAttributeSet.Get(); }

	void InitAbilityActorInfo(APawn* InAvatarActor);

#pragma endregion Gameplay Ability System

};
