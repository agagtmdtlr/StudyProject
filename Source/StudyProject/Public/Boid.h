// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <cstdint>
#include "Boid.generated.h"

/**
 * 
 */
//UCLASS()
//class STUDYPROJECT_API UBoid : public UObject
//{
//	GENERATED_BODY()
//	
//};



USTRUCT()
struct FBoid
{
	GENERATED_BODY()
public:
	using BoidUuid = uint32;


	FBoid();

	bool operator<(const FBoid& rhs) const;

	FORCEINLINE bool IsValid() const { return Uuid != std::numeric_limits<BoidUuid>::max(); }

public:	
	UPROPERTY(VisibleAnywhere)
	FVector Position;

	UPROPERTY(VisibleAnywhere)
	FVector Velocity;

	UPROPERTY(VisibleAnywhere)
	FVector Goal;

	UPROPERTY(VisibleAnywhere)
	FRotator GoalRotator;

	UPROPERTY(VisibleAnywhere)
	uint32 Uuid;
};
