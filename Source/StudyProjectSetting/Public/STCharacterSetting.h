// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "STCharacterSetting.generated.h"

/**
 * 
 */
UCLASS(config=StudyProject)
class STUDYPROJECTSETTING_API USTCharacterSetting : public UObject
{
	GENERATED_BODY()

public:

	USTCharacterSetting();
	
	UPROPERTY(config)
	TArray<FSoftObjectPath> CharacterAssets;
};
