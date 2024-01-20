// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "GameFramework/SaveGame.h"
#include "STSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USTSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	USTSaveGame();

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int32 HighScore;

	UPROPERTY()
	int32 CharacterIndex;
};
