// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Actors/NEB_Item.h"

// Engine Includes
#include "Components/SphereComponent.h"

// Project Includes
#include "Characters/NEB_Character.h"
#include "Characters/NEB_PlayerCharacter.h"
#include "GameplayAbilitySystem/NEB_AbilitySystemComponent.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_Item::ANEB_Item()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComponent"));
	RootComponent = SphereCollisionComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent.Get());

	AbilitySystemComponent = CreateDefaultSubobject<UNEB_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bShouldAttachToHolder = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_Item::BeginPlay()
{
	Super::BeginPlay();

	if(SphereCollisionComponent)
	{
		SphereCollisionComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ANEB_Item::OnPickupCollisionBeginOverlap);
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
void ANEB_Item::OnPickupCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bShouldAttachToHolder)
	{
		return;
	}

	if(ANEB_PlayerCharacter* PlayerCharacter = Cast<ANEB_PlayerCharacter>(OtherActor))
	{
		PlayerCharacter->EquipItem(this);
	}
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

