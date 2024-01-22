// Fill out your copyright notice in the Description page of Project Settings.


#include "Boid/BoidActionModel.h"


UBoidActionModel::UBoidActionModel()
{
	FrameIndex = 0;
}

void UBoidActionModel::UpdateConstraint(double GridSize)
{
	CohesionRadiusSquare = GridSize;
	SeparationRadiusSquare = GridSize * 0.3;
}


void UBoidActionModel::SetBoundary(FBox NewBoundary)
{
	Boundary = NewBoundary;
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
			if( Neighbor == Boid )
				continue;

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
	

	//Boid->GoalRotator = FQuat::MakeFromRotationVector(Boid->Velocity);
	//Boid->GoalRotator.Quaternion();
}

void UBoidActionModel::CheckCollisionBoundary(FBoid* Boid)
{
	float RayLength = 100.0f;
	FVector CheckPos = Boid->Position + Boid->Velocity.GetSafeNormal() * RayLength;
	FVector NewVelocity = Boid->Velocity;

	FVector BoxVertices[8];
	Boundary.GetVertices(BoxVertices);
	if (Boundary.Min.X > CheckPos.X || Boundary.Max.X < CheckPos.X)
		NewVelocity.X = -NewVelocity.X;

	if (Boundary.Min.Y > CheckPos.Y || Boundary.Max.Y < CheckPos.Y)
		NewVelocity.Y = -NewVelocity.Y;

	if(Boundary.Min.Z > CheckPos.Z || Boundary.Max.Z < CheckPos.Z)
		NewVelocity.Z = -NewVelocity.Z;
}
