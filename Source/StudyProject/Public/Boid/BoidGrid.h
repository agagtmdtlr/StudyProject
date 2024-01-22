// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "StudyProject.h"
#include "Boid/Boid.h"
#include <vector>
#include <set>
#include <unordered_map>
#include "Templates/Function.h"
#include <type_traits>

/**
 * 
 */


template<typename T>
struct TBoidCell
{
	FORCEINLINE TBoidCell();
	void Insert(T* Element);
	void Erase(T* Element);
	void ForEach(TFunctionRef<void(T*, std::vector<TBoidCell<T>*>&)> Executer);

	FIntVector Index;
	FVector Min;
	FVector Max;

	std::vector<TBoidCell<T>*> NearestCells;

	std::set<T*> Elements;
};

template<typename T>
void TBoidCell<T>::ForEach(TFunctionRef<void(T*, std::vector<TBoidCell<T>*>&)> Executer )
{
	if (IsBound(Executer))
	{
		for (T* Element : Elements)
		{
			Executer(Element , NearestCells);
		}
	}
}

template<typename T>
void TBoidCell<T>::Erase(T* Element)
{
	Elements.erase(Element);
}

template<typename T>
void TBoidCell<T>::Insert(T* Element)
{	
	Elements.insert(Element);
}

template<typename T>
FORCEINLINE TBoidCell<T>::TBoidCell()
{
}

template<typename T>
struct TBoidGrid
{
	//static_assert(std::is_base_of<UBoid,T>, "T muse be derived UBoid Class");

public:
	FORCEINLINE TBoidGrid(FIntVector Dimensions);
	void Insert(T* Element, FIntVector Index);
	void Erase(T* Element, FIntVector Index);
	FORCEINLINE TBoidCell<T>& At(FIntVector Index);

	FORCEINLINE bool InnerBoundary(FIntVector Index) const;

	TArray<TBoidCell<T>*> GetNearestCells(FIntVector Index);

	FIntVector Size;

	std::vector<TBoidCell<T>> Cells; // 3D to linear list
};

template<typename T>
FORCEINLINE bool TBoidGrid<T>::InnerBoundary(FIntVector Index) const
{
	if (Index.X < 0 || Index.X >= Size.X)
		return false;

	if (Index.Y < 0 || Index.Y >= Size.Y)
		return false;

	if (Index.Z < 0 || Index.Z >= Size.Z)
		return false;

	return true;
}

template<typename T>
TArray<TBoidCell<T>*> TBoidGrid<T>::GetNearestCells(FIntVector Index)
{
	TArray<TBoidCell<T>*> NearestCells;
	//std::vector<TBoidCell<T>*> NearestCells;
	NearestCells.Reserve(27);

	constexpr int dr[3] = { -1,0,1 };
	for (int i = 0; i < 27; ++i)
	{
		FIntVector NewIndex(Index.X + dr[ i % 3 ], Index.Y + dr[(i % 9) / 3], Index.Z + dr[i / 9]);
		if (InnerBoundary(NewIndex))
		{
			NearestCells.Add(&At(NewIndex));
			//NearestCells.push_back(&At(NewIndex));
			//At(NewIndex).Index = NewIndex;
		}
	}

	return NearestCells;
}

template<typename T>
FORCEINLINE TBoidCell<T>& TBoidGrid<T>::At(FIntVector Index)
{
	check(InnerBoundary(Index));
	return Cells[ Size.X * ( Size.Y  * Index.Z + Index.Y ) + Index.X];
}

template<typename T>
void TBoidGrid<T>::Insert(T* Element, FIntVector Index)
{
	check(InnerBoundary(Index));
	At(Index).Insert(Element);
}

template<typename T>
void TBoidGrid<T>::Erase(T* Element, FIntVector Index)
{
	check(InnerBoundary(Index));
	At(Index).Erase(Element);
}

template<typename T>
FORCEINLINE TBoidGrid<T>::TBoidGrid(FIntVector Dimensions)
	:Size(Dimensions)
{
	Cells.resize( Dimensions.X * Dimensions.Y * Dimensions.Z);

	int CellSize = Cells.size();

	int PlaneSize = Dimensions.X * Dimensions.Y;
	for (int i = 0; i < CellSize; i++)
	{
		FIntVector NewIndex(i % Dimensions.X, ( i % PlaneSize) / Dimensions.Y, i / PlaneSize);
		Cells[i].Index = NewIndex;
	}
}

using FBoidCell = TBoidCell<FBoid>;
using FBoidGrid = TBoidGrid<FBoid>;
