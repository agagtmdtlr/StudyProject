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
UCLASS(BlueprintType, Blueprintable, config = Game, meta = (ShortTooltip = "The BoidActionModel is an object that defines how a Boid is simulated."))
class STUDYPROJECT_API UBoidActionModel : public UObject
{
	GENERATED_BODY()

public:
	UBoidActionModel();
	
	virtual void UpdateConstraint(double GridSize);

	virtual void UpdateBoid(FBoid* Boid, const TArray<FBoidCell*>& NearestCells, float DeltaTime);
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Range")
	double SeparationRadius;

	UPROPERTY(VisibleAnywhere, Category = "Range")
	double CohesionRadius;

	UPROPERTY(EditAnywhere, Category = "Range")
	double AlignmentSpeed;

private:
	FVector MinPosition;
	FVector MaxPosition;

	double SeparationRadiusSquare;

	double CohesionRadiusSquare;

	int32 FrameIndex;

};
