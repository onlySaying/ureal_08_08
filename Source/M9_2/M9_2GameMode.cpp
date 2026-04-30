// Copyright Epic Games, Inc. All Rights Reserved.

#include "M9_2GameMode.h"
#include "M9_2Character.h"
#include "UObject/ConstructorHelpers.h"

AM9_2GameMode::AM9_2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
