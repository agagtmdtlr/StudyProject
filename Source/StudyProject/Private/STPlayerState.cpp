// Fill out your copyright notice in the Description page of Project Settings.


#include "STPlayerState.h"

ASTPlayerState::ASTPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
}

int32 ASTPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 ASTPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

void ASTPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Destiny"));
	CharacterLevel = 5;
	GameScore = 0;
}
