// Fill out your copyright notice in the Description page of Project Settings.


#include "STSection.h"

// Sets default values
ASTSection::ASTSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bNoBattle = false;

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

	// Create Trigger
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	Trigger->SetCollisionProfileName(TEXT("STTrigger"));


	// Create Socket Gate Mesh
	static FName GateSockets[] = {
		{TEXT("+XGate")},
		{TEXT("-XGate")},
		{TEXT("+YGate")},
		{TEXT("-YGate")}
	};

	for (FName GateSocket : GateSockets)
	{
		// Create Gate
		STCHECK(Mesh->DoesSocketExist(GateSocket));
		UStaticMeshComponent* NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
		NewGate->SetStaticMesh(SM_Gate.Object);
		NewGate->SetupAttachment(RootComponent, GateSocket);
		NewGate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));

		GateMeshes.Add(NewGate);

		// Create Gate Trigger

		UBoxComponent* NewGateTrigger = CreateDefaultSubobject<UBoxComponent>( *GateSocket.ToString().Append(TEXT("Trigger")));
		NewGateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		NewGateTrigger->SetupAttachment(RootComponent, GateSocket);
		NewGateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		NewGateTrigger->SetCollisionProfileName(TEXT("STTrigger"));
		GateTriggers.Add(NewGateTrigger);

	}



}

// Called when the game starts or when spawned
void ASTSection::BeginPlay()
{
	Super::BeginPlay();


	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}



// Called every frame
void ASTSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTSection::SetState(ESectionState NewState)
{
	switch (NewState)
	{
	case ASTSection::ESectionState::READY:
	{
		Trigger->SetCollisionProfileName(TEXT("STTrigger"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}

		OperateGates(true);
		break;
	}
	case ASTSection::ESectionState::BATTLE:
	{
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}

		OperateGates(true);
		break;
	}
	case ASTSection::ESectionState::COMPLETE:
	{
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("STTrigger"));
		}
		break;
	}
	}

	CurrentState = NewState;

}

void ASTSection::OperateGates(bool bOpen /*= true*/)
{
	for (UStaticMeshComponent* Gate : GateMeshes)
	{
		Gate->SetRelativeRotation(bOpen ? FRotator(0.0f, 90.0f, 0.0f) : FRotator::ZeroRotator);
	}
}

