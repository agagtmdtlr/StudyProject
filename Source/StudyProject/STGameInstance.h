// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USTGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USTGameInstance();

	virtual void Init() override;
};
