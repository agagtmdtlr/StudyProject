// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "GameFramework/GameModeBase.h"
#include "STGameMode.generated.h"



/**
 * 
 */
UCLASS()
class STUDYPROJECT_API ASTGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASTGameMode();

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void AddScore(class ASTPlayerController* ScoredPlayer);
	int32 GetScore() const;

private:
	UPROPERTY()
	class ASTGameState* STGameState;

	UPROPERTY()
	int32 ScoreToClear;
};
