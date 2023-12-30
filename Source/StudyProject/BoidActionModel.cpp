// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidActionModel.h"


UBoidActionModel::UBoidActionModel()
{
	FrameIndex = 0;
}

void UBoidActionModel::UpdateBoid(FBoid* Boid, const TArray<FBoidCell*>& NearestCells, float DeltaTime)
{
	FVector Goal = FVector::ZeroVector;
	FVector Goal2 = FVector::ZeroVector;


	int32 cohesionNum = 0;
	int32 separationNum = 0;

	for (const FBoidCell* Cell : NearestCells)
	{
		for (const FBoid* Neighbor : Cell->Elements)
		{
			FVector toNeighbor = Neighbor->Position - Boid->Position;

			double NeighborLengthSq = toNeighbor.SquaredLength();
			if (CohesionRadiusSquare >= NeighborLengthSq)
			{
				cohesionNum++;
				Goal += toNeighbor;

				if (SeparationRadiusSquare >= NeighborLengthSq)
				{
					separationNum++;
					Goal2 += -toNeighbor;
				}
			}
		}
	}

	if (cohesionNum > 0)
	{
		Goal /= cohesionNum;
	}

	if (separationNum > 0)
	{
		Goal2 /= separationNum;
	}

	FVector NewVelocity = Goal + Goal2;
	NewVelocity = NewVelocity.GetSafeNormal();

	Boid->Velocity = FMath::Lerp(Boid->Velocity.GetSafeNormal(), NewVelocity, FVector(DeltaTime));
}
