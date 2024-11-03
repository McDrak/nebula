// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "UObject/Interface.h"

// Generated Header Included Last
#include "NEB_AIStateInterface.generated.h"

enum class ENEB_AIState : uint8;

UINTERFACE(MinimalAPI)
class UNEB_AIStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * TODO
 */
class NEBULA_API INEB_AIStateInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ENEB_AIState BP_GetAIState() const;
};
