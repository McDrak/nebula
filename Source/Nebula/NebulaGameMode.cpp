// Copyright Epic Games, Inc. All Rights Reserved.

#include "NebulaGameMode.h"
#include "NebulaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANebulaGameMode::ANebulaGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
