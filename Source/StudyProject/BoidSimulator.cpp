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

	//BoidActionModel = CreateDefaultSubobject<UBoidActionModel>(TEXT("BoidActionModel"));
	
	UuidGenerator = 0;
}

// Called when the game starts or when spawned
void ABoidSimulator::BeginPlay()
{
	Super::BeginPlay();

	Resize(FIntVector(10, 10, 10));

	static FVector MinPosition;
	MinPosition = GetActorLocation() - BoxHalfSize + ( GridSize * 0.5f );
	static FVector MaxPosition;
	MaxPosition = GetActorLocation() + BoxHalfSize - ( GridSize * 0.5f );

	int32 ElementCount = 10000;

	BoidInstances.SetNum(ElementCount);
	InstanceMeshTranforms.SetNum(ElementCount);


	for (int i = 0; i < ElementCount; ++i)
	{
		FVector NewPosition;
		NewPosition.X = FMath::RandRange(MinPosition.X, MaxPosition.X);
		NewPosition.Y = FMath::RandRange(MinPosition.Y, MaxPosition.Y);
		NewPosition.Z = FMath::RandRange(MinPosition.Z, MaxPosition.Z);

		
		FBoid& NewBoid = BoidInstances[i];
		NewBoid.Position = NewPosition;
		NewBoid.Uuid = GeneratorBoidUuid();
		
		FTransform& Transform = InstanceMeshTranforms[NewBoid.Uuid];
		Transform = FTransform(NewPosition);


		Insert(&NewBoid);
	}

	// update instnace Transform
	for (FBoid& Instance : BoidInstances)
	{
		FTransform& Transform = InstanceMeshTranforms[Instance.Uuid];
		Transform = FTransform(Instance.Position);
	}

	ISMCompoent->AddInstances(InstanceMeshTranforms, false, true);

	
}

// Called every frame
void ABoidSimulator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();	

	UBoidActionModel* ActionModel = Cast<UBoidActionModel>(BoidActionModel);
	STCHECK(ActionModel == nullptr);

	for (FBoidCell& Cell : Grid->Cells)
	{
		if (Cell.Elements.empty()) continue;

		TArray<FBoidCell*> NearestCells = Grid->GetNearestCells(Cell.Index);

		for (FBoid* Element : Cell.Elements)
		{
			ActionModel->UpdateBoid(Element, NearestCells, DeltaTime);
		}

	}


	ISMCompoent->BatchUpdateInstancesTransforms(0, InstanceMeshTranforms, true);
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
	BoxHalfSize = FVector(NewSize) / 2 * GridSize;

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
	return currentUuid;
}

void ABoidSimulator::Insert(FBoid* NewBoid)
{
	FVector CenterPosition = GetActorLocation();

	FVector MinLocation = CenterPosition - BoxHalfSize;
	static FVector LocalPosition;
	LocalPosition = NewBoid->Position - MinLocation;
	LocalPosition -= FVector(GridSize * 0.5f); // floor to lower
	static FIntVector LocalIndex; 
	LocalIndex = FIntVector(LocalPosition.GridSnap(GridSize) / GridSize);
	
	Grid->Insert(NewBoid, LocalIndex);
}

