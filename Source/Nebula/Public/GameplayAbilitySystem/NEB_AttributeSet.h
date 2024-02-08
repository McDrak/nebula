// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Framework Includes
#include "AttributeSet.h"

// Project Includes
#include "NEB_AttributeSet.generated.h"

/**
 * Base class for the Attribute Set in the Nebula Project 
 */
UCLASS()
class NEBULA_API UNEB_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UNEB_AttributeSet();
};
