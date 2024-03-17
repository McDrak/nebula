// Fill out your copyright notice in the Description page of Project Settings.

// Main Header Included First
#include "Characters/NEB_PlayerCharacter.h"

// Engine Includes
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Project Includes
#include "GameFramework/NEB_PlayerController.h"
#include "GameFramework/NEB_PlayerState.h"
#include "GameplayAbilitySystem/NEB_AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/NEB_PlayerAttributeSet.h"

//----------------------------------------------------------------------------------------------------------------------
ANEB_PlayerCharacter::ANEB_PlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCameraComponent"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMeshComponent"));
	FirstPersonMeshComponent->SetOnlyOwnerSee(true);
	FirstPersonMeshComponent->SetupAttachment(FirstPersonCameraComponent.Get());
	FirstPersonMeshComponent->bCastDynamicShadow = false;
	FirstPersonMeshComponent->CastShadow = false;
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AddInputMappingContext(MainInputMappingContext.Get());
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerControllerPtr = Cast<ANEB_PlayerController>(NewController);

	if(ANEB_PlayerState* CurrentPlayerState = GetPlayerState<ANEB_PlayerState>())
	{
		AbilitySystemComponent = Cast<UNEB_AbilitySystemComponent>(CurrentPlayerState->GetAbilitySystemComponent());
		AttributeSet = CurrentPlayerState->GetNEBAttributeSet();

		CurrentPlayerState->InitAbilityActorInfo(this);

		InitializeAttributes();
		GrantInitialCharacterAbilities();
		ApplyStartupCharacterEffects();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if(ANEB_PlayerState* CurrentPlayerState = GetPlayerState<ANEB_PlayerState>())
	{
		AbilitySystemComponent = Cast<UNEB_AbilitySystemComponent>(CurrentPlayerState->GetAbilitySystemComponent());
		AttributeSet = CurrentPlayerState->GetNEBAttributeSet();

		CurrentPlayerState->InitAbilityActorInfo(this);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction.Get(), ETriggerEvent::Triggered, this, &ANEB_PlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction.Get(), ETriggerEvent::Triggered, this, &ANEB_PlayerCharacter::Look);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2d MovementVector = Value.Get<FVector2d>();
	if(GetController())
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2d LookAxisVector = Value.Get<FVector2d>();
	if(GetController())
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::AddInputMappingContext(const UInputMappingContext* InputMappingContextToGive)
{
	if(const ANEB_PlayerController* PlayerController = Cast<ANEB_PlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			InputSubsystem->AddMappingContext(InputMappingContextToGive, 0);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ANEB_PlayerCharacter::RemoveInputMappingContext(const UInputMappingContext* InputMappingContextToRemove)
{
	if(const ANEB_PlayerController* PlayerController = Cast<ANEB_PlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			InputSubsystem->RemoveMappingContext(InputMappingContextToRemove);
		}
	}
}
