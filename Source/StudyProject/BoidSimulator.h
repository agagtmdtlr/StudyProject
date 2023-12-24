// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoidGrid.h"
#include "BoidSimulator.generated.h"

class UBoid;
class UInstancedStaticMeshComponent;
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
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Component")
	UInstancedStaticMeshComponent* ISMCompoent;

	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMesh* MeshToInstance;

	UPROPERTY(EditAnywhere, Category = "Grid")
	double GridSize; // 10.0f;

	UPROPERTY(EditAnywhere, Category = "Grid")
	FIntVector CellSize;

	//UPROPERTY(EditAnywhere, Category = "Boid")
	//TSubclassOf<UBoid> Boid;


private:
	//void Insert(UBoid* boid);
	//void Resize(FIntVector NewSize);

	FVector BoxHalfSize;
	
	
	//TUniquePtr<FBoidGrid> Grid;
};

