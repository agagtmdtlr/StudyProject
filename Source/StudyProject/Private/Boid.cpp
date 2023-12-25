// Fill out your copyright notice in the Description page of Project Settings.


#include "Boid.h"

FBoid::FBoid()
	:
	Position(FVector::Zero()),
	Velocity(FVector::Zero()),
	Goal(FVector::Zero()),
	GoalRotator(FRotator::ZeroRotator),
	Uuid(std::numeric_limits<BoidUuid>::max())

{

}

bool FBoid::operator<(const FBoid& rhs) const
{
	return Uuid < rhs.Uuid;
}
