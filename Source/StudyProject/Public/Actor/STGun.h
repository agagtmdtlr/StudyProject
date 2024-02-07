// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "STGun.generated.h"

class ASTProjectile;

#define STGUN_MAX_BULLET_COUNT (40)

UCLASS()
class STUDYPROJECT_API ASTGun : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ASTGun();

	static const uint32 BulletMaxCount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Projectile", Meta = (AllowPrivateAccess = true))
	TSubclassOf<ASTProjectile> BulletClass;

	TStaticArray<ASTProjectile*, STGUN_MAX_BULLET_COUNT> Bullets;	
};
