// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BoidBehavior.generated.h"

UCLASS()
class STUDYPROJECT_API UBoidBehavior : public UObject
{
	GENERATED_BODY()

public:
	UBoidBehavior() {};
	virtual ~UBoidBehavior() {};

	//void ExecuteAction(class ABoid* Boid, const TArray<class ABoid*>& Neighbors) {};


private:
	UPROPERTY(EditAnywhere, Category = "Range")
		double SeparationRadius;

	UPROPERTY(EditAnywhere, Category = "Range")
		double CohesionRadius;

	UPROPERTY(EditAnywhere, Category = "Range")
		double AlignmentSpeed;
};




