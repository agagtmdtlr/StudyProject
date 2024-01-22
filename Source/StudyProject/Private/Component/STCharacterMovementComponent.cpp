// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/STCharacterMovementComponent.h"
#include "Actor/STCharacter.h"

USTCharacterMovementComponent::USTCharacterMovementComponent(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	:UCharacterMovementComponent(ObjectInitializer)
{

}

void USTCharacterMovementComponent::PlaneMovement(const FVector2D& Value)
{
	ASTCharacter* STCharacter = Cast<ASTCharacter>(GetCharacterOwner());
	FVector2D Value2D = Value;

	Value2D *= Acceleration;

	FRotationMatrix RotationMatrix = FRotationMatrix(FRotator(0.0f, STCharacter->GetControlRotation().Yaw, 0.0f));
	ASTCharacter::EControlMode ControlMode = STCharacter->GetControlMode();

	switch (ControlMode)
	{
	case ASTCharacter::EControlMode::Orbit:
	{
		AddInputVector(RotationMatrix.GetUnitAxis(EAxis::X) * Value2D.Y);
		AddInputVector(RotationMatrix.GetUnitAxis(EAxis::Y) * Value2D.X);
		break;
	}
	case ASTCharacter::EControlMode::TopView:
	{
		DirectionToMove.X = Value2D.Y;
		DirectionToMove.Y = Value2D.X;
	}
	}
}

void USTCharacterMovementComponent::AccelerateMovement(const bool& IsPressed)
{
	if (IsPressed)
	{
		Acceleration = 1.0f;
	}
	else
	{
		Acceleration = 0.5f;
	}
}



void USTCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ASTCharacter* STCharacter = GetSTCharacter();

	ASTCharacter::EControlMode ControlMode = GetControlMode();
	switch (ControlMode)
	{
	case ASTCharacter::EControlMode::TopView:
	{
		if (DirectionToMove.SizeSquared() > KINDA_SMALL_NUMBER)
		{
			AddInputVector(DirectionToMove);
		}
		break;
	}
	}
}

FVector USTCharacterMovementComponent::GetDirectionToMove() const
{
	return DirectionToMove;
}

ASTCharacter* USTCharacterMovementComponent::GetSTCharacter()
{
	ASTCharacter* STCharacter = Cast<ASTCharacter>(GetCharacterOwner());
	STCHECK(STCharacter != nullptr, nullptr);

	return STCharacter;
}

ASTCharacter::EControlMode USTCharacterMovementComponent::GetControlMode()
{
	ASTCharacter* STCharcter = GetSTCharacter();
	return STCharcter->GetControlMode();
}
