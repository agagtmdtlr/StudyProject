// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "GameFramework/PlayerState.h"
#include "STPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API ASTPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASTPlayerState();

	int32 GetGameScore() const;
	int32 GetCharacterLevel() const;

	void InitPlayerData();

protected:
	UPROPERTY(Transient)
	int32 GameScore;

	UPROPERTY(Transient)
	int32 CharacterLevel;

	
};
