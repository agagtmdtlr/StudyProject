// Fill out your copyright notice in the Description page of Project Settings.


#include "STPlayerState.h"
#include "STGameInstance.h" // for STCharacterData
#include "STSaveGame.h" // for USTGameSave

ASTPlayerState::ASTPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	GameHighScore = 0;
	Exp = 0;

	SaveSlotName = TEXT("Player1");
}

int32 ASTPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 ASTPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

int32 ASTPlayerState::GetGameHighScore() const
{
	return GameHighScore;
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
	SavePlayerData();

	return DidLevelUp;
}

void ASTPlayerState::AddGameScore()
{
	GameScore++;
	if (GameScore >= GameHighScore)
	{
		GameHighScore = GameScore;
	}

	OnPlayerStateChanged.Broadcast();
	SavePlayerData();
}

void ASTPlayerState::InitPlayerData()
{

	auto STSaveGame = Cast<USTSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (STSaveGame == nullptr)
	{
		STSaveGame = GetMutableDefault<USTSaveGame>();
	}

	SetPlayerName(STSaveGame->PlayerName);
	SetCharacterLevel(STSaveGame->Level);
	GameScore = 0;
	GameHighScore = STSaveGame->HighScore;
	Exp = STSaveGame->Exp;

	SavePlayerData();
}

void ASTPlayerState::SavePlayerData()
{
	USTSaveGame* NewPlayerData = NewObject<USTSaveGame>();
	NewPlayerData->PlayerName = GetPlayerName();
	NewPlayerData->Level = GetCharacterLevel();
	NewPlayerData->Exp = Exp;
	NewPlayerData->HighScore = GetGameHighScore();

	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		STLOG(Error, TEXT("SaveGame Error"));
	}
}

void ASTPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	STCHECK(STGameInstance != nullptr);

	CurrentStatData = STGameInstance->GetSTCharacterData(NewCharacterLevel);
	STCHECK(CurrentStatData != nullptr);

	CharacterLevel = NewCharacterLevel;
}
