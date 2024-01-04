// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "AIController.h"
#include "STAIController.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API ASTAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASTAIController();
	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;
};
