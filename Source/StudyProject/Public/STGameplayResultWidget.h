// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "STGameplayWidget.h"
#include "STGameplayResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USTGameplayResultWidget : public USTGameplayWidget
{
	GENERATED_BODY()
	
public:
	void BindGameState(class ASTGameState* GameState);

protected:
	virtual void NativeConstruct() override;

private:
	TWeakObjectPtr<class ASTGameState> CurrentGameState;

};
