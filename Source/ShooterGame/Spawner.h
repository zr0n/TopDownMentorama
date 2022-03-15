// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class SHOOTERGAME_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> SpawnTemplate;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float IntervalToSpawn;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float IntervalDecrementPerWave;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SpawnQuantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ObjectsPerLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ActorsToSpawn;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CurrentLevel;

	UFUNCTION(BlueprintCallable)
	void SpawnFromTemplate();

	UFUNCTION(BlueprintCallable)
	void LevelUp();

	UFUNCTION(BlueprintCallable)
	void ResetSpawnerWithDelay();

	UFUNCTION(BlueprintCallable)
	void ResetSpawnerImmediately();
	
	
protected:

	float Counter;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
