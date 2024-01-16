// Fill out your copyright notice in the Description page of Project Settings.


#include "STPlayerState.h"
#include "STGameInstance.h" // for STCharacterData

ASTPlayerState::ASTPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	Exp = 0;
}

int32 ASTPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 ASTPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

float ASTPlayerState::GetExpRatio() const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
		return 0.0f;

	float Result = (float)Exp / (float)CurrentStatData->NextExp;
	STLOG(Warning, TEXT("Ratio : %f , Current : %d, Next : %d"), Result, Exp, CurrentStatData->NextExp);
	return Result;
}

bool ASTPlayerState::AddExp(int32 IncomExp)
{
	if (CurrentStatData->NextExp == -1)
		return false;

	bool DidLevelUp = false;
	Exp = Exp + IncomExp;
	if (Exp >= CurrentStatData->NextExp)
	{
		Exp -= CurrentStatData->NextExp;
		SetCharacterLevel(CharacterLevel + 1);
		DidLevelUp = true;
	}

	OnPlayerStateChanged.Broadcast();
	return DidLevelUp;
}

void ASTPlayerState::AddGameScore()
{
	GameScore++;
	OnPlayerStateChanged.Broadcast();
}

void ASTPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Destiny"));
	SetCharacterLevel(5);
	GameScore = 0;
	Exp = 0;
}

void ASTPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	STCHECK(STGameInstance != nullptr);

	CurrentStatData = STGameInstance->GetSTCharacterData(NewCharacterLevel);
	STCHECK(CurrentStatData != nullptr);

	CharacterLevel = NewCharacterLevel;
}
