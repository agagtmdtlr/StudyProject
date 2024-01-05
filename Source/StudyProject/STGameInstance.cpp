// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameInstance.h"


USTGameInstance::USTGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/Book/GameData/STCharacterData.STCharacterData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_STCharacter(*CharacterDataPath);

	STCHECK(DT_STCharacter.Succeeded());
	STCharacterTable = DT_STCharacter.Object;
	STCHECK(STCharacterTable->GetRowMap().Num() > 0);
}

void USTGameInstance::Init()
{
	Super::Init();

	STLOG(Warning, TEXT("DropExp of Level 20 STCharcter : %d"), GetSTCharacterData(20)->DropExp );
}

FSTCharacterData* USTGameInstance::GetSTCharacterData(int32 Level)
{
	return STCharacterTable->FindRow<FSTCharacterData>(*FString::FromInt(Level),TEXT(""));
}
