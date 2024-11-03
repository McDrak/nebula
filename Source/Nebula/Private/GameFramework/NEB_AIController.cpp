// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "GameFramework/NEB_AIController.h"

// Engine Includes
#include "Components/StateTreeAIComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_AIController::ANEB_AIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	StateTreeAIComponent = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeAIComponent"));
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_AIController::BeginPlay()
{
	Super::BeginPlay();

	if(PerceptionComponent)
	{
		PerceptionComponent->OnPerceptionUpdated.AddUniqueDynamic(this, &ANEB_AIController::ANEB_AIController::OnPerceptionUpdated);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_AIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
}
