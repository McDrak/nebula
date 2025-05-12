// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "GameFramework/NEB_AIController.h"

// Engine Includes
#include "Components/StateTreeAIComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"

// Project Includes
#include "Definitions/NEB_AIDefinitions.h"
#include "Interfaces/NEB_AIStateInterface.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_AIController::ANEB_AIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	StateTreeAIComponent = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeAIComponent"));

	AAIController::SetGenericTeamId(FGenericTeamId(static_cast<uint8>(ENEB_TeamID::Enemies)));
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_AIController::BeginPlay()
{
	Super::BeginPlay();

	if(PerceptionComponent)
	{
		PerceptionComponent->OnTargetPerceptionInfoUpdated.AddUniqueDynamic(this, &ANEB_AIController::ANEB_AIController::OnTargetPerceptionInfoUpdated);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_AIController::OnSightPerceptionUpdated(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	if(UpdateInfo.Stimulus.WasSuccessfullySensed())
	{
		INEB_AIStateInterface::Execute_BP_SetAIState(GetPawn(), ENEB_AIState::Combat);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_AIController::OnHearingPerceptionUpdated(const FActorPerceptionUpdateInfo& UpdateInfo)
{
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_AIController::OnTargetPerceptionInfoUpdated(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	if(UpdateInfo.Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		OnSightPerceptionUpdated(UpdateInfo);
		return;
	}

	if(UpdateInfo.Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
	{
		OnHearingPerceptionUpdated(UpdateInfo);
	}
}
