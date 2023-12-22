// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidSimulator.h"
#include "Boid.h"
#include "DrawDebugHelpers.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
ABoidSimulator::ABoidSimulator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridSize = 10.0;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Contaniner"));
	ISMCompoent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ISMCompoent"));
	

	RootComponent = ISMCompoent;
}

// Called when the game starts or when spawned
void ABoidSimulator::BeginPlay()
{
	Super::BeginPlay();
	Resize(FIntVector(10, 10, 10));
	
	


}

// Called every frame
void ABoidSimulator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	

	

	
}

void ABoidSimulator::Resize(FIntVector NewSize)
{
	if (GridSize <= 0.0)
	{
		STLOG_S(Warning);
	}


	CellSize = NewSize;

	Grid.Release();
	Grid = TUniquePtr<FBoidGrid>(new FBoidGrid(NewSize));
	BoxHalfSize = FVector(NewSize) * GridSize;

	UWorld* World = GetWorld();

	FVector Location = GetActorLocation();

	FVector MinLocation = Location - BoxHalfSize;

	double GridExtent = GridSize * 0.5;
	
	for (int x = 0; x < NewSize.X; ++x)
	{
		for (int y = 0; y < NewSize.Y; ++y)
		{
			for (int z = 0; z < NewSize.Z; ++z)
			{

				FVector DrawLocation = MinLocation + FVector(x * GridSize, y * GridSize, z * GridSize);
				DrawLocation += FVector(GridExtent);

				DrawDebugBox(World, DrawLocation , FVector(GridSize), FQuat::Identity, FColor::Red, true);

			}
		}
	}



}

void ABoidSimulator::Insert(ABoid* NewBoid)
{
	FVector CenterPosition = GetActorLocation();
	FVector MinLocation = CenterPosition - BoxHalfSize;

	FVector BoidLocation = NewBoid->GetActorLocation();
	FVector LocalPosition = BoidLocation - MinLocation;
	FIntVector LocalIndex(LocalPosition.GridSnap(GridSize) / GridSize);

	Grid->Insert(NewBoid, LocalIndex);

}
