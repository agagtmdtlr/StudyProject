// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Boid.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API UBoid : public UObject
{
	GENERATED_BODY()
	
};

USTRUCT()
struct FBoidStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
		FVector Position;

	UPROPERTY(VisibleAnywhere)
		FVector Velocity;

	UPROPERTY(VisibleAnywhere)
		FVector Goal;

	UPROPERTY(VisibleAnywhere)
		FRotator GoalRotator;
};
