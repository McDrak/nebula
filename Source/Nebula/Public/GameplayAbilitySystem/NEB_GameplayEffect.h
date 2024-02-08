// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Framework Includes
#include "GameplayEffect.h"

// Generated Header Included Last
#include "NEB_GameplayEffect.generated.h"

/**
 * Base class for the Gameplay Effects in the Nebula Project
 */
UCLASS()
class NEBULA_API UNEB_GameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UNEB_GameplayEffect();
};
