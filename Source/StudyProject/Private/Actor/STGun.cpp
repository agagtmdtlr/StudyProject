// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/STGun.h"

#include "Actor/STProjectile.h"


const uint32 ASTGun::BulletMaxCount = STGUN_MAX_BULLET_COUNT;

// Sets default values
ASTGun::ASTGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	uint32 InstanceID = 0;
	

}

// Called when the game starts or when spawned
void ASTGun::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	// Bullet spawn
	{
		FActorSpawnParameters SpawnParameter;
		SpawnParameter.Owner = this;
		FTransform SpawnTransform;

		int32 InstanceID = 0;

		for (ASTProjectile* BulletInstance : Bullets)
		{
			SpawnParameter.Name = FName( FString::Printf(TEXT("Bullet_%d"), InstanceID) );
			GetWorld()->SpawnActor<ASTProjectile>(BulletClass,SpawnTransform,SpawnParameter);
			InstanceID++;
		}
	}

	
	
}

// Called every frame
void ASTGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

