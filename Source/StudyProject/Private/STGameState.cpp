// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameState.h"

ASTGameState::ASTGameState()
{
	TotalGameScore = 0;
}

int32 ASTGameState::GetTotalGameScore() const
{
	return TotalGameScore;
}

void ASTGameState::AddGameScore()
{
	TotalGameScore++;
}
