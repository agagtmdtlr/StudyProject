// Fill out your copyright notice in the Description page of Project Settings.

#include "STItemBox.h"
#include "STWeapon.h"
#include "STCharacter.h"

// Sets default values
ASTItemBox::ASTItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	Effect->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	/// Script / Engine.StaticMesh'/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Box(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if (SM_Box.Succeeded())
	{
		Box->SetStaticMesh(SM_Box.Object);
	}

	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
	if (P_CHESTOPEN.Succeeded())
	{
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false;
	}

	WeaponItemClass = ASTWeapon::StaticClass();
}

// Called when the game starts or when spawned
void ASTItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASTItemBox::OnCharacterOverlap);
}

// Called every frame
void ASTItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void ASTItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STLOG_S(Warning);

	auto STCharacter = Cast<ASTCharacter>(OtherActor);
	STCHECK(STCharacter != nullptr);
	if (STCharacter != nullptr && WeaponItemClass != nullptr)
	{
		if (STCharacter->CanSetWeapon())
		{
			auto NewWeapon = GetWorld()->SpawnActor<ASTWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			STCharacter->SetWeapon(NewWeapon);

			// Equip Effect 
			const bool bReset = true;
			Effect->Activate(bReset);
			Box->SetHiddenInGame(true, true);
			SetActorEnableCollision(false);
			Effect->OnSystemFinished.AddDynamic(this, &ASTItemBox::OnEffectFinished);	

		}
		else
		{
			ST_LOG(Warning, TEXT("%s can't equip weapon currently"), *STCharacter->GetName());
		}
	}
}

void ASTItemBox::OnEffectFinished(class UParticleSystemComponent* PSystem)
{
	Destroy();
}

