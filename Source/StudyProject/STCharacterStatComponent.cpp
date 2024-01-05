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
		SetHP(CurrentStatData->MaxHP);
	}
	else
	{
		STLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void USTCharacterStatComponent::SetDamage(float NewDamage)
{
	STCHECK(CurrentStatData != nullptr);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
	
}

void USTCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	// KINDA_SMALL_NUMBER : float precision error
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		OnHPIsZero.Broadcast();
	}
}


float USTCharacterStatComponent::GetAttack()
{
	STCHECK(CurrentStatData != nullptr, 0.0f);
	return CurrentStatData->Attack;
}

float USTCharacterStatComponent::GetHPRatio()
{
	STCHECK(CurrentStatData != nullptr, 0.0f);

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : ( CurrentHP / CurrentStatData->MaxHP );
}

