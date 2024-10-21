// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Framework Includes
#include "AbilitySystemInterface.h"

// Generated Header Included Last
#include "NEB_Item.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UNEB_AbilitySystemComponent;
class ANEB_Character;

/**
 * TODO
 */
UCLASS()
class NEBULA_API ANEB_Item : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ANEB_Item();

#pragma region AActor

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

#pragma endregion AActor

#pragma region IAbilitySystemInterface

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

#pragma endregion IAbilitySystemInterface

#pragma region Components

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UNEB_AbilitySystemComponent> AbilitySystemComponent;

#pragma endregion Components

#pragma region Pick Up

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pick Up")
	uint8 bShouldAttachToHolder : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pick Up", meta = (EditCondition = "bShouldAttachToHolder == true", EditConditionHides = true))
	FName PickUpSocketName;

	TWeakObjectPtr<ANEB_Character> CurrentHolderCharacterPtr;

	TWeakObjectPtr<ANEB_Character> PreviousHolderCharacterPtr;

	UFUNCTION()
	void OnPickupCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	virtual void OnItemPickedUp(ANEB_Character* EquippingCharacter);

	virtual void OnItemDropped();

#pragma endregion Pick Up

};
