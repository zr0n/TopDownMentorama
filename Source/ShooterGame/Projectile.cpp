// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "ShooterGameCharacter.h"
#include "EnemyCharacter.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(BoxCollision);

	InitialLifeSpan = 10.f;
	ShotSpeed = 300.f;

	Damage = 34;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::MoveForward(const float DeltaT)
{
	const FVector Offset  = GetActorForwardVector() * DeltaT * ShotSpeed;
	AddActorWorldOffset(Offset);
}

bool AProjectile::IsEnemy(const AShooterGameCharacter* Character)
{
	if(!Character)
		return false;
	
	return Character->GetClass()->IsChildOf(AEnemyCharacter::StaticClass());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveForward(DeltaTime);
}

void AProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AShooterGameCharacter* OtherCharacter = Cast<AShooterGameCharacter>(OtherActor);

	if(!IsValid(OtherCharacter) || !IsEnemy(OtherCharacter))
		return;

	OtherCharacter->ReceiveDamage(Damage);
	Destroy();
}

