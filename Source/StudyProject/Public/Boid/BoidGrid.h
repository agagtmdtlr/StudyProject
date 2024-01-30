// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "StudyProject.h"
#include "Boid/Boid.h"
#include <set>
#include <unordered_map>
#include "Templates/Function.h"

#include "Spatial/SparseGrid3.h"


using namespace UE::Geometry;
/**
 * 
 */
struct FBoidCell
{
	std::set<FBoid*> Elements;
	FVector3i Index;
};

struct FBoidGrid
{
	//static_assert(std::is_base_of<UBoid,FBoid>, "FBoid muse be derived UBoid Class");

public:
	FORCEINLINE FBoidGrid(FVector3i Dimensions);
	FORCEINLINE FBoidCell* At(FVector3i Index);

	
	FORCEINLINE bool InnerBoundary(FVector3i Index) const;
	FORCEINLINE void FreeAll();
	FORCEINLINE void Insert(FVector3i Index, FBoid* NewBoid);

	FORCEINLINE TArray<FBoidCell*> GetNearestCells(FVector3i Index);

	TSparseGrid3<FBoidCell> Cells;
	//TSparseGrid3<FBoidCell> Cells;

	FVector3i Size;
};

FORCEINLINE FBoidGrid::FBoidGrid(FVector3i Dimensions)
	:Size(Dimensions)
{

}

FORCEINLINE void FBoidGrid::FreeAll()
{
	Cells.FreeAll();
}

FORCEINLINE void FBoidGrid::Insert(FVector3i Index, FBoid* NewBoid)
{
	if (Cells.Has(Index))
	{
		FBoidCell* Cell = Cells.Get(Index, false);
		Cell->Elements.insert(NewBoid);
	}
	else
	{
		FBoidCell* Cell = Cells.Get(Index, true);
		Cell->Index = Index;
		Cell->Elements.insert(NewBoid);
	}

}

FORCEINLINE bool FBoidGrid::InnerBoundary(FVector3i Index) const
{
	if (Index.X < 0 || Index.X >= Size.X)
		return false;

	if (Index.Y < 0 || Index.Y >= Size.Y)
		return false;

	if (Index.Z < 0 || Index.Z >= Size.Z)
		return false;

	return true;
}

FORCEINLINE TArray<FBoidCell*> FBoidGrid::GetNearestCells(FVector3i Index)
{
	TArray<FBoidCell*> NearestCells;
	NearestCells.Reserve(27);

	constexpr int dr[3] = { -1,0,1 };
	for (int i = 0; i < 27; ++i)
	{
		FVector3i NewIndex(Index.X + dr[ i % 3 ], Index.Y + dr[(i % 9) / 3], Index.Z + dr[i / 9]);
		if (InnerBoundary(NewIndex))
		{
			if( Cells.Has(NewIndex))
				NearestCells.Add(Cells.Get(NewIndex, false));
		}
	}

	return NearestCells;
}


FORCEINLINE FBoidCell* FBoidGrid::At(FVector3i Index)
{
	check(InnerBoundary(Index));	
	return Cells.Get(Index, false);
}


