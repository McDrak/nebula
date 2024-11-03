// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Generated Header Included Last
#include "NEB_SplinePath.generated.h"

class USplineComponent;

UCLASS()
class NEBULA_API ANEB_SplinePath : public AActor
{
	GENERATED_BODY()

public:
	ANEB_SplinePath();

#pragma region Components

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USplineComponent> SplineComponent;

#pragma endregion Components
};
