// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Boid.h"
#include "BoidGrid.h"
#include "BoidActionModel.generated.h"


struct FBoid;
/**
 * 
 */
UCLASS()
class STUDYPROJECT_API UBoidActionModel : public UObject
{
	GENERATED_BODY()

public:
	void UpdateBoid(FBoid* Boid, const TArray<FBoidCell*>& NearestCells);
	
private:
	UPROPERTY(EditAnywhere, Category = "Range")
		double SeparationRadius;

	UPROPERTY(EditAnywhere, Category = "Range")
		double CohesionRadius;

	UPROPERTY(EditAnywhere, Category = "Range")
		double AlignmentSpeed;
};
