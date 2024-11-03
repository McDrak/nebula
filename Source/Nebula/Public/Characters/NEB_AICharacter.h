// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Project Includes
#include "Characters/NEB_Character.h"
#include "Interfaces/NEB_AIStateInterface.h"
#include "Interfaces/NEB_NavigableObjectInterface.h"

// Generated Header Included Last
#include "NEB_AICharacter.generated.h"

class ANEB_SplinePath;

/**
 * TODO
 */
UCLASS()
class NEBULA_API ANEB_AICharacter : public ANEB_Character, public INEB_NavigableObjectInterface, public INEB_AIStateInterface
{
	GENERATED_BODY()

public:
	ANEB_AICharacter(const FObjectInitializer& ObjectInitializer);

#pragma region INEB_NavigableObjectInterface

	virtual ANEB_SplinePath* BP_GetAssignedSplinePath_Implementation() const override { return AssignedPatrollingSplinePath; }

	virtual int32 BP_GetSplineCurrentSplinePathPoint_Implementation() const override { return CurrentSplinePathPoint; };

	virtual void BP_SetCurrentSplinePathPoint_Implementation(const int32 NewSplinePathPoint) override { CurrentSplinePathPoint = NewSplinePathPoint; };

#pragma endregion INEB_NavigableObjectInterface

#pragma region INEB_AIStateInterface

public:
	virtual ENEB_AIState BP_GetAIState_Implementation() const override { return CurrentAIState; };

#pragma endregion INEB_AIStateInterface

#pragma region AIStates

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Character|AI States")
	ENEB_AIState CurrentAIState;

#pragma endregion AIStates

#pragma region Patrolling

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AI Character|Patrolling")
	TObjectPtr<ANEB_SplinePath> AssignedPatrollingSplinePath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Character|Patrolling")
	int32 CurrentSplinePathPoint;

#pragma endregion Patrolling
};
