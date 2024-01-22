// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "Blueprint/UserWidget.h"
#include "STHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USTHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class USTCharacterStatComponent* CharacterStat);
	void BindPlayerState(class ASTPlayerState* PlayerState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

private:
	TWeakObjectPtr<class USTCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<class ASTPlayerState> CurrentPlayerState;

	UPROPERTY()
	class UProgressBar* HPBar;

	UPROPERTY()
	class UProgressBar* ExpBar;

	UPROPERTY()
	class UTextBlock* PlayerName;

	UPROPERTY()
	class UTextBlock* PlayerLevel;

	UPROPERTY()
	class UTextBlock* CurrentScore;

	UPROPERTY()
	class UTextBlock* HighScore;
	
};
