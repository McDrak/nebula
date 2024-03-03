// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Actors/NEB_Item.h"

// Engine Includes
#include "Components/SphereComponent.h"

// Project Includes
#include "Characters/NEB_Character.h"
#include "GameplayAbilitySystem/NEB_AbilitySystemComponent.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_Item::ANEB_Item()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComponent"));
	RootComponent = SphereCollisionComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent.Get());

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent.Get());

	AbilitySystemComponent = CreateDefaultSubobject<UNEB_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bShouldRemoveStaticMeshOnInit = false;
	bShouldRemoveSkeletalMeshOnInit = false;
	bShouldAttachToHolder = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Item::BeginPlay()
{
	Super::BeginPlay();

	if(bShouldRemoveStaticMeshOnInit && StaticMeshComponent)
	{
		StaticMeshComponent->DestroyComponent();
	}

	if(bShouldRemoveSkeletalMeshOnInit && SkeletalMeshComponent)
	{
		SkeletalMeshComponent->DestroyComponent();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//----------------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent* ANEB_Item::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Item::OnItemPickedUp(ANEB_Character* EquippingCharacter)
{
	if(!EquippingCharacter)
	{
		return;
	}

	CurrentHolderCharacterPtr = EquippingCharacter;

	if(bShouldAttachToHolder)
	{
		const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(EquippingCharacter->GetMesh(), AttachmentTransformRules, PickUpSocketName);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Item::OnItemDropped()
{
	PreviousHolderCharacterPtr = CurrentHolderCharacterPtr;
	CurrentHolderCharacterPtr = nullptr;

	if(bShouldAttachToHolder)
	{
		const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, false);
		DetachFromActor(DetachmentTransformRules);
	}
}

