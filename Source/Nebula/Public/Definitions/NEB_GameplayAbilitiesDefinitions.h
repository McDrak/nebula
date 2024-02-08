// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Framework Includes
#include "AttributeSet.h"
#include "GameplayTagContainer.h"

// Generated Header Included Last
#include "NEB_GameplayAbilitiesDefinitions.generated.h"

class UNEB_GameplayEffect;

/**
 * Struct that helps to apply a Gameplay Effect unto something
 * Can be used with only the class but also allows the use of SetByCaller Tags for Duration and Magnitudes,
 * Specific Backing Attributes, Specific Level and DynamicGrantedTags.
 */
USTRUCT(BlueprintType)
struct FNEB_GameplayEffectSetup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UNEB_GameplayEffect> GameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier Magnitude")
	float EffectLevelMagnitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier Magnitude")
	FGameplayTag SetByCallerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier Magnitude")
	uint8 bUseAttributeMagnitude : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier Magnitude", meta = (EditCondition = "bUseAttributeMagnitude == true", EditConditionHides))
	FGameplayAttribute BackingAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier Magnitude", meta = (EditCondition = "bUseAttributeMagnitude == false", EditConditionHides))
	float SetByCallerMagnitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration")
	uint8 bShouldModifyDuration : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration", meta = (EditCondition = "bShouldModifyDuration == true", EditConditionHides))
	uint8 bIsDynamicDuration : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration", meta = (EditCondition = "bShouldModifyDuration == true && bIsDynamicDuration == false", EditConditionHides))
	float DurationMagnitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration", meta = (EditCondition = "bShouldModifyDuration == true && bIsDynamicDuration == false", EditConditionHides))
	FGameplayTag SetByCallerDurationTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer DynamicGrantedTags;

	FNEB_GameplayEffectSetup()
		: EffectLevelMagnitude(0.f), bUseAttributeMagnitude(false), SetByCallerMagnitude(0.f), bShouldModifyDuration(false), bIsDynamicDuration(false), DurationMagnitude(0.f)
	{
	}

	FNEB_GameplayEffectSetup(const float NewEffectLevelMagnitude, const bool bNewUseAttributeMagnitude, const float NewSetByCallerMagnitude, const bool bNewShouldModifyDuration, const bool bNewIsDynamicDuration, const float NewDurationMagnitude)
		: EffectLevelMagnitude(NewEffectLevelMagnitude), bUseAttributeMagnitude(bNewUseAttributeMagnitude), SetByCallerMagnitude(NewSetByCallerMagnitude), bShouldModifyDuration(bNewShouldModifyDuration), bIsDynamicDuration(bNewIsDynamicDuration), DurationMagnitude(NewDurationMagnitude)
	{
	}
};
