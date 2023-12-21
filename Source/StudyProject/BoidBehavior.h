// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BoidBehavior.generated.h"

UCLASS(abstract)
class STUDYPROJECT_API UBoidBehavior : public UObject
{
	GENERATED_BODY()

public:
	UBoidBehavior();
	virtual ~UBoidBehavior() {};

	virtual void ExecuteAction(class ABoid* Boid, const TArray<class ABoid*>& Neighbors);
};

UBoidBehavior::UBoidBehavior()
{

}

void UBoidBehavior::ExecuteAction(class ABoid* Boid, const TArray<class ABoid*>& Neighbors)
{

}


