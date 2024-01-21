// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "GameFramework/GameStateBase.h"
#include "STGameState.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API ASTGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASTGameState();

public:
	int32 GetTotalGameScore() const;
	void AddGameScore();

	void SetGameCleared();
	bool IsGameCleared() const;

private:
	UPROPERTY(Transient)
	int32 TotalGameScore;

	UPROPERTY(Transient)
	bool bGameCleared;
	
};
