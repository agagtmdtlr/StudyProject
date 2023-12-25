// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidSimulator.h"
#include "DrawDebugHelpers.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
ABoidSimulator::ABoidSimulator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridSize = 10.0;

	//MeshToInstance
	ISMCompoent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ISMCompoent"));
	RootComponent = ISMCompoent;
	ISMCompoent->SetStaticMesh(MeshToInstance);
	
	UuidGenerator = 0;
}

// Called when the game starts or when spawned
void ABoidSimulator::BeginPlay()
{
	Super::BeginPlay();

	Resize(FIntVector(10, 10, 10));

	FVector MinPosition = GetActorLocation() - BoxHalfSize;
	FVector MaxPosition = GetActorLocation() + BoxHalfSize;

	for (int i = 0; i < 100; ++i)
	{
		FVector NewPosition;
		NewPosition.X = FMath::RandRange(MinPosition.X, MaxPosition.X);
		NewPosition.Y = FMath::RandRange(MinPosition.Y, MaxPosition.Y);
		NewPosition.Z = FMath::RandRange(MinPosition.Z, MaxPosition.Z);

		FBoid NewBoid;
		BoidInstances.Add(NewBoid);

		

		//Insert(&BoidInstances.Last() );
	}
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
	Grid = TUniquePtr<TBoidGrid<FBoid>>(new TBoidGrid<FBoid>(NewSize));
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


FBoid::BoidUuid ABoidSimulator::GeneratorBoidUuid()
{
	FBoid::BoidUuid currentUuid  = UuidGenerator;
	UuidGenerator++;
	return currentUuid
}

void ABoidSimulator::Insert(FVector BoidLocation)
{
	FVector CenterPosition = GetActorLocation();
	FVector MinLocation = CenterPosition - BoxHalfSize;
	FVector LocalPosition = BoidLocation - MinLocation;
	FIntVector LocalIndex(LocalPosition.GridSnap(GridSize) / GridSize);

	FBoid NewBoid;
	NewBoid.Position = BoidLocation;

	Grid->Insert(NewBoid, LocalIndex);

}

