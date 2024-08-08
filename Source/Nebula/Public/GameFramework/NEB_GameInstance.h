// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// Generated Header Included Last
#include "NEB_GameInstance.generated.h"

/**
 * Game Instance class for Nebula Project
 */
UCLASS()
class NEBULA_API UNEB_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UNEB_GameInstance();

#pragma region UGameInstance

protected:
	virtual void Init() override;

#pragma endregion UGameInstance
};
