// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "GameFramework/PlayerState.h"
#include "STPlayerState.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

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
	int32 GetGameHighScore() const;
	int32 GetCharacterIndex() const;
	FString SaveSlotName;


	float GetExpRatio() const;


	bool AddExp(int32 IncomExp);
	void AddGameScore();

	void InitPlayerData();
	void SavePlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged; // for update widget

protected:
	UPROPERTY(Transient)
	int32 GameScore;

	UPROPERTY(Transient)
	int32 GameHighScore;

	UPROPERTY(Transient)
	int32 CharacterLevel;

	UPROPERTY(Transient)
	int32 Exp;

	UPROPERTY(Transient)
	int32 CharacterIndex;

private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	struct FSTCharacterData* CurrentStatData;

	
};
