// Fill out your copyright notice in the Description page of Project Settings.


#include "STCharacterStatComponent.h"
#include "STGameInstance.h"

// Sets default values for this component's properties
USTCharacterStatComponent::USTCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	bWantsInitializeComponent = true; // 

	Level = 1;
}


// Called when the game starts
void USTCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetNewLevel(Level);
}


void USTCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void USTCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto STGameInstance = Cast<USTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	STCHECK(STGameInstance != nullptr);
	CurrentStatData = STGameInstance->GetSTCharacterData(NewLevel);
	if (CurrentStatData != nullptr)
	{
		Level = NewLevel;
		CurrentHP = CurrentStatData->MaxHP;
	}
	else
	{
		ST_LOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void USTCharacterStatComponent::SetDamage(float NewDamage)
{
	STCHECK(CurrentStatData != nullptr);
	CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP);
	ST_LOG(Warning, TEXT("CurrentHP : (%f)"), CurrentHP);
	if (CurrentHP <= 0.0f)
	{
		OnHPIsZero.Broadcast();
	}
}

float USTCharacterStatComponent::GetAttack()
{
	STCHECK(CurrentStatData != nullptr, 0.0f);
	return CurrentStatData->Attack;
}
