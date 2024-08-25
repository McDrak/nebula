// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"

// Project Includes
#include "Characters/NEB_Character.h"

// Generated Header Included Last
#include "NEB_PlayerCharacter.generated.h"

class USpringArmComponent;
class UNEB_PlayerAttributeSet;
class UCameraComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class ANEB_PlayerController;

/**
 * Character for Players on the Nebula Project
 */
UCLASS()
class NEBULA_API ANEB_PlayerCharacter : public ANEB_Character
{
	GENERATED_BODY()

public:
	ANEB_PlayerCharacter(const FObjectInitializer& ObjectInitializer);

#pragma region AActor

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

#pragma endregion AActor

#pragma region APawn

public:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

#pragma endregion APawn

#pragma region Components

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> CameraBoomComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY()
	TObjectPtr<UNEB_PlayerAttributeSet> PlayerAttributeSet;

public:
	UNEB_PlayerAttributeSet* GetPlayerAttributeSet() const { return PlayerAttributeSet; }

#pragma endregion Components

#pragma region General References

protected:
	TWeakObjectPtr<ANEB_PlayerController> PlayerControllerPtr;

public:
	ANEB_PlayerController* GetNEBPlayerController() const { return PlayerControllerPtr.Get(); }

#pragma endregion General References

#pragma region Inputs

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UInputMappingContext> MainInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UInputAction> LookAction;

	void EnableCameraRotationMovement(const FInputActionValue& Value);

	void DisableCameraRotationMovement(const FInputActionValue& Value);

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

public:
	void AddInputMappingContext(const UInputMappingContext* InputMappingContextToGive);
	void RemoveInputMappingContext(const UInputMappingContext* InputMappingContextToRemove);

#pragma endregion Inputs

#pragma region Camera

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly ,Category = "Camera")
	uint8 bIsCameraOverRightShoulder : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Camera")
	FVector InitialCameraSocketOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly ,Category = "Camera")
	FVector ShoulderIdlePosition;

#pragma endregion Camera

};
