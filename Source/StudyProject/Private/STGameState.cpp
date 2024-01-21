// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameState.h"

ASTGameState::ASTGameState()
{
	TotalGameScore = 0;
	bGameCleared = false;
}

int32 ASTGameState::GetTotalGameScore() const
{
	return TotalGameScore;
}

void ASTGameState::AddGameScore()
{
	TotalGameScore++;
}

void ASTGameState::SetGameCleared()
{
	bGameCleared = true;
}

bool ASTGameState::IsGameCleared() const
{
	return bGameCleared;
}
