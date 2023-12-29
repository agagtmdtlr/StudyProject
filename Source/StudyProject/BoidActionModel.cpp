// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidActionModel.h"


void UBoidActionModel::UpdateBoid(FBoid* Boid, const TArray<FBoidCell*>& NearestCells)
{
	for (const FBoidCell* Cell : NearestCells)
	{
		for (const FBoid* Neighbor : Cell->Elements)
		{

		}
	}
}
