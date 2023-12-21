// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "StudyProject.h"
#include "GameFramework/Actor.h"
#include <vector>
#include <set>
#include <unordered_map>
#include "Templates/Function.h"
#include <type_traits>

/**
 * 
 */


template<typename T>
struct TCell
{
	FORCEINLINE TCell();
	void Insert(T Element);
	void Erase(T Element);
	void ForEach(TFunctionRef<void(T&)> Executer);

	FIntVector Index;
	FVector Min;
	FVector Max;


	std::set<T> Elements;


};

template<typename T>
void TCell<T>::ForEach(TFunctionRef<void(T&)> Executer )
{
	if (IsBound(Executer))
	{
		for (T& Element : Elements)
		{
			Executer(Element);
		}
	}
}

template<typename T>
void TCell<T>::Erase(T Element)
{
	Elements.erase(Element);
}

template<typename T>
void TCell<T>::Insert(T Element)
{	
	Elements.insert(Element);
}

template<typename T>
FORCEINLINE TCell<T>::TCell()
{
}

template<typename T>
struct TGrid
{
	//static_assert(std::is_base_of<AActor,T>, "T muse be derived AActor Class");

public:
	FORCEINLINE TGrid(FIntVector Dimensions);
	void Insert(T Element, FIntVector Index);
	FORCEINLINE TCell<T>& At(FIntVector Index);

	FORCEINLINE bool InnerBoundary(FIntVector Index) const;

	std::vector<TCell<T>*> GetNearestCells(FIntVector Index);

	FIntVector Size;

	std::vector<TCell<T>> Cells; // 3D to linear list
};

template<typename T>
FORCEINLINE bool TGrid<T>::InnerBoundary(FIntVector Index) const
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
std::vector<TCell<T>*> TGrid<T>::GetNearestCells(FIntVector Index)
{
	std::vector<TCell<T>*> NearestCells;
	NearestCells.reserve(27);

	constexpr int dr[3] = { -1,0,1 };
	for (int i = 0; i < 27; ++i)
	{
		FIntVector NewIndex(Index.X + dr[ i % 3 ], Index.Y + dr[(i % 9) / 3], Index.Z + dr[i / 9]);
		if (InnerBoundary(NewIndex))
		{
			NearestCells.push_back(&At(NewIndex));
			//At(NewIndex).Index = NewIndex;
		}
	}

	return NearestCells;
}

template<typename T>
FORCEINLINE TCell<T>& TGrid<T>::At(FIntVector Index)
{
	return Cells[ Size.X * ( Size.Y  * Index.Z + Index.Y ) + Index.X];
}

template<typename T>
void TGrid<T>::Insert(T Element, FIntVector Index)
{
	TCell& Cell = At(Index);
	At(Index).Insert(Element);
}

template<typename T>
FORCEINLINE TGrid<T>::TGrid(FIntVector Dimensions)
	:Size(Dimensions)
{
	Cells.resize( Dimensions.X * Dimensions.Y * Dimensions.Z);

	int size = Cells.size();

	int planeSize = Dimensions.X * Dimensions.Y;
	for (int i = 0; i < size; i++)
	{
		FIntVector NewIndex(i % Dimensions.X, ( i % planeSize ) / Dimensions.Y, i / planeSize );
		Cells[i].Index = NewIndex;
	}
}

using FGrid = TGrid<AActor*>;
