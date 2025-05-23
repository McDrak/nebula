// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "AIController.h"

// Generated Header Included Last
#include "NEB_AIController.generated.h"

struct FActorPerceptionUpdateInfo;
class UStateTreeAIComponent;

UCLASS()
class NEBULA_API ANEB_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ANEB_AIController(const FObjectInitializer& ObjectInitializer);

#pragma region AActor

protected:
	virtual void BeginPlay() override;

#pragma endregion AActor

#pragma region Components

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStateTreeAIComponent> StateTreeAIComponent;

#pragma endregion Components

#pragma region Perception

protected:
	virtual void OnSightPerceptionUpdated(const FActorPerceptionUpdateInfo& UpdateInfo);

	virtual void OnHearingPerceptionUpdated(const FActorPerceptionUpdateInfo& UpdateInfo);

	UFUNCTION()
	virtual void OnTargetPerceptionInfoUpdated(const FActorPerceptionUpdateInfo& UpdateInfo);

#pragma endregion Perception
};
