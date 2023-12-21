// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidSimulator.h"
#include "Boid.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABoidSimulator::ABoidSimulator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxHalfSize = FVector(50, 50, 50);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Contaniner"));

	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void ABoidSimulator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoidSimulator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	DrawDebugBox(World, GetActorLocation(), BoxHalfSize, FQuat::Identity, FColor::Red, false, 0.f);
}

void ABoidSimulator::Resize(FIntVector NewSize)
{
	Grid.Release();
	Grid = TUniquePtr<FGrid>(new FGrid(NewSize));

	

}

void ABoidSimulator::Insert(ABoid* Boid)
{
	FVector CenterPosition = GetActorLocation();
	Boid->GetActorLocation();
}
