// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/STSection.h"
#include "Actor/STCharacter.h"
#include "Actor/STItemBox.h"
#include "Controller/STPlayerController.h"
#include "STGameMode.h"

// Sets default values
ASTSection::ASTSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bNoBattle = false;

	EnemySpawnTime = 2.0f;
	ItemBoxSpawnTime = 5.0f;

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

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASTSection::OnTriggerBeginOverlap);


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


		NewGateTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASTSection::OnGateTriggerBeginOverlap);
		// 어떤 문에 있는 컴포넌트 인지 구분하기 위해 태그 설정
		NewGateTrigger->ComponentTags.Add(GateSocket);
	}



}

void ASTSection::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
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

		OperateGates(false);

		GetWorld()->GetTimerManager().SetTimer(SpawnNPCTimerHandle, FTimerDelegate::CreateUObject(this, &ASTSection::OnNPCSpawn), EnemySpawnTime, false);
		GetWorld()->GetTimerManager().SetTimer(SpawnItemBoxTimerHandle, FTimerDelegate::CreateLambda([this]()->void
			{
				FVector2D RandXY = FMath::RandPointInCircle(600.0f);
				GetWorld()->SpawnActor<ASTItemBox>(GetActorLocation() + FVector(RandXY, 30.0f), FRotator::ZeroRotator);
			}), ItemBoxSpawnTime, false);


		break;
	}
	case ASTSection::ESectionState::COMPLETE:
	{
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("STTrigger"));
		}

		// game score add

		OperateGates(true);
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

void ASTSection::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CurrentState == ESectionState::READY)
	{
		SetState(ESectionState::BATTLE);
	}
}

void ASTSection::OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STCHECK(OverlappedComponent->ComponentTags.Num() == 1);
	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	FName SocketName = FName(*ComponentTag.ToString().Left(2));
	if (!Mesh->DoesSocketExist(SocketName))
		return;

	FVector NewLocation = Mesh->GetSocketLocation(SocketName);

	TArray<FOverlapResult> OverlapResults;

	const bool bInTraceComplex = false;
	AActor* ignoreActor = this;// 범위내 오버랩 객체 중 자기자신은 무시하기 위함
	FCollisionQueryParams CollsionQueryParam(NAME_None, bInTraceComplex, ignoreActor); 
	FCollisionObjectQueryParams ObjectQueryparam(FCollisionObjectQueryParams::InitType::AllObjects);
	bool bResult = GetWorld()->OverlapMultiByObjectType(OverlapResults, NewLocation, FQuat::Identity, ObjectQueryparam, FCollisionShape::MakeSphere(775.0f), CollsionQueryParam);

	if (!bResult)
	{
		auto NewSection = GetWorld()->SpawnActor<ASTSection>(NewLocation, FRotator::ZeroRotator);
	}
	else
	{
		STLOG(Warning, TEXT("New Section area is not empty"));
	}

}

void ASTSection::OnNPCSpawn()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnNPCTimerHandle); //
	auto KeyNPC =  GetWorld()->SpawnActor<ASTCharacter>(GetActorLocation() + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
	if (KeyNPC != nullptr)
	{
		KeyNPC->OnDestroyed.AddDynamic(this, &ASTSection::OnKeyNPCDestroyed);
	}
}

void ASTSection::OnKeyNPCDestroyed(AActor* DestroyedActor)
{
	auto STCharacter = Cast<ASTCharacter>(DestroyedActor);
	STCHECK(STCharacter != nullptr);

	auto STPlayerController = Cast<ASTPlayerController>(STCharacter->LastHitBy);
	STCHECK(STPlayerController != nullptr);

	auto STGameMode = Cast<ASTGameMode>(GetWorld()->GetAuthGameMode());
	STCHECK(STGameMode != nullptr);
	STGameMode->AddScore(STPlayerController);

	SetState(ESectionState::COMPLETE);
}

