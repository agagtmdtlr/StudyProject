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
	// TODO:: Blackboard �Ӽ��̸��� �ϵ��ڵ� ��, ���� �ʿ�...
	static const FName HomePosKey;
	static const FName PatrolPosKey;


	ASTAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;
	
	UPROPERTY()
	class UBlackboardData* BBAsset;

};
