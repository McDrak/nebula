// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "UObject/Interface.h"

// Generated Header Included Last
#include "NEB_NavigableObjectInterface.generated.h"

class ANEB_SplinePath;

UINTERFACE(MinimalAPI)
class UNEB_NavigableObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * TODO
 */
class NEBULA_API INEB_NavigableObjectInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ANEB_SplinePath* BP_GetAssignedSplinePath() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 BP_GetSplineCurrentSplinePathPoint() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BP_SetCurrentSplinePathPoint(const int32 NewSplinePathPoint);
};
