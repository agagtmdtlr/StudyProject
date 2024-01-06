// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "Blueprint/UserWidget.h"
#include "STCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USTCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class USTCharacterStatComponent* NewCharacterStat);
	
protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class USTCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;

	UPROPERTY()
	class UProgressBar* MPProgressBar;
};
