// Fill out your copyright notice in the Description page of Project Settings.


#include "STSection.h"

// Sets default values
ASTSection::ASTSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	FString AssetPath = TEXT("/Game/BackGround/StaticMesh/SM_SQUARE.SM_SQUARE");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Square(*AssetPath);
	if (SM_Square.Succeeded())
	{
		Mesh->SetStaticMesh(SM_Square.Object);
	}
	else
	{
		STLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *AssetPath);
	}

	FString GateAssetPath = TEXT("/Game/BackGround/StaticMesh/SM_GATE.SM_GATE");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Gate(*GateAssetPath);
	if (!SM_Gate.Succeeded())
	{
		STLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *GateAssetPath);
	}

	static FName GateSockets[] = {
		{TEXT("+XGate")},
		{TEXT("-XGate")},
		{TEXT("+YGate")},
		{TEXT("-YGate")}
	};

	for (FName GateSocket : GateSockets)
	{
		STCHECK(Mesh->DoesSocketExist(GateSocket));
		UStaticMeshComponent* NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
		NewGate->SetStaticMesh(SM_Gate.Object);
		NewGate->SetupAttachment(RootComponent, GateSocket);
		NewGate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));

		GateMeshes.Add(NewGate);
	}

}

// Called when the game starts or when spawned
void ASTSection::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
