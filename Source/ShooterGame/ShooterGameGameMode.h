// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameGameMode.generated.h"

class ASpawner;
UCLASS(minimalapi)
class AShooterGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterGameGameMode();
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<ASpawner*> Spawners;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class AShooterGameCharacter* PlayerCharacter;

	virtual void Tick(float DeltaSeconds) override;

	void CheckNextLevel();
};



