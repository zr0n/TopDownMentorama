// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

#include "ShooterGameGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IntervalToSpawn = 3.f;
	IntervalDecrementPerWave = .6f;

	SpawnQuantity = 10.f;
	ObjectsPerLevel = 5;

	CurrentLevel = 0x00;

}

void ASpawner::SpawnFromTemplate()
{
	if(auto World = GetWorld())
	{
		World->SpawnActor<AActor>(SpawnTemplate, GetActorLocation(), GetActorRotation());
		ActorsToSpawn++;
	}
}

void ASpawner::LevelUp()
{
	CurrentLevel++;
	IntervalToSpawn -= IntervalDecrementPerWave;
	SpawnQuantity += ObjectsPerLevel * CurrentLevel;
}

void ASpawner::ResetSpawnerWithDelay()
{
	if(const auto World  = GetWorld())
	{
		FTimerHandle TimerHandle;
		World->GetTimerManager().SetTimer(TimerHandle, this, &ASpawner::ResetSpawnerImmediately, 5.f, false);
	}
}

void ASpawner::ResetSpawnerImmediately()
{
	ActorsToSpawn = SpawnQuantity;
	Counter = 0x00;
}


// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	if(!HasAuthority())
		return;
	
	ResetSpawnerImmediately();
	
	if(const auto GM = Cast<AShooterGameGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GM->Spawners.AddUnique(this);
	}
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ActorsToSpawn <= 0)
		return;

	Counter += DeltaTime;

	if(Counter >= IntervalToSpawn)
	{
		Counter = 0x00;
		SpawnFromTemplate();
		
	}

}

