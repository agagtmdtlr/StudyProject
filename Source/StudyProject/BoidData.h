// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BoidData.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API UBoidData : public UObject
{
	GENERATED_BODY()
	
public:

public:
	FVector Position;

	FVector Velocity;

	FVector Goal;

	FRotator GoalRotator;
};
