// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "GameFramework/Actor.h"
#include "STWeapon.generated.h"

UCLASS()
class STUDYPROJECT_API ASTWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(VisibleAnywhere, Category=Weapon)
	USkeletalMeshComponent* Weapon;
};
