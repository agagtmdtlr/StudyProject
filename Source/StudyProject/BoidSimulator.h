// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.h"
#include "BoidSimulator.generated.h"

class ABoid;
struct BoidContainer;

UCLASS()
class STUDYPROJECT_API ABoidSimulator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoidSimulator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Insert(ABoid* boid);
	void Resize(FIntVector NewSize);

	FVector BoxHalfSize;
	TUniquePtr<FGrid> Grid;
};

