// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

UENUM(Blueprintable, BlueprintType)
enum class ENEB_AIState : uint8
{
	None,
	Patrolling,
	Combat,
	Fleeing,
};