// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid/BoidGrid.h"
#include "Boid/Boid.h"
#include "Boid/BoidActionModel.h"
#include "BoidSimulator.generated.h"

class UInstancedStaticMeshComponent;

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

	void DrawDebugBoundardy();


private:
	UPROPERTY(EditAnywhere, Category = "Component")
	UInstancedStaticMeshComponent* ISMCompoent;

	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMesh* MeshToInstance;

	UPROPERTY(EditAnywhere, Category = "Grid")
	double GridSize; 

	UPROPERTY(EditAnywhere, Category = "Grid")
	FIntVector CellSize;

	UPROPERTY(EditAnywhere, Category = "Boid")
	UBoidActionModel* BoidActionModel;

	UPROPERTY(EditAnywhere, Category="Boid")
	int32 ElementCount;

	UPROPERTY(EditAnywhere, Category=Debug)
	bool bDebugBoundary;
	 

private:
	void Insert(FBoid* NewBoid);
	void Resize(FIntVector NewSize);

	FBoid::BoidUuid GeneratorBoidUuid();

	FVector BoxHalfSize;
	
	TUniquePtr<TBoidGrid<FBoid>> Grid;

	TArray<FBoid> BoidInstances;
	TArray<FTransform> InstanceMeshTranforms;

	FBoid::BoidUuid UuidGenerator;
};

