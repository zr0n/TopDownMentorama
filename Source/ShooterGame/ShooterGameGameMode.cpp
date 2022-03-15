// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGameGameMode.h"
#include "ShooterGamePlayerController.h"
#include "ShooterGameCharacter.h"
#include "Spawner.h"
#include "UObject/ConstructorHelpers.h"

AShooterGameGameMode::AShooterGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AShooterGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AShooterGameGameMode::Tick(float DeltaSeconds)
{
	CheckNextLevel();
}

void AShooterGameGameMode::CheckNextLevel()
{
	if(!Spawners.Num())
		return;

	for(const auto Spawner : Spawners)
	{
		if(Spawner->ActorsToSpawn)
			return;
	}
	
	for(const auto Spawner : Spawners)
	{
		Spawner->ResetSpawnerWithDelay();
	}
}
