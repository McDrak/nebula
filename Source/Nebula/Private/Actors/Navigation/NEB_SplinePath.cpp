// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Actors/Navigation/NEB_SplinePath.h"

// Engine Includes
#include "Components/SplineComponent.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_SplinePath::ANEB_SplinePath()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

