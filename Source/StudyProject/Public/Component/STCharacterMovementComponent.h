// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STCharacter.h"
#include "STCharacterMovementComponent.generated.h"


class ASTCharacter;
/**
 * 
 */
UCLASS(Blueprintable)
class STUDYPROJECT_API USTCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	USTCharacterMovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
	void PlaneMovement(const FVector2D& Value);
	

	UFUNCTION(BlueprintCallable)
	void AccelerateMovement(const bool& IsPressed);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	FVector GetDirectionToMove() const;;

	void OnControlModeChanged();


private:
	ASTCharacter* GetSTCharacter();
	ASTCharacter::EControlMode GetControlMode();

	float Acceleration = 0.5f;

	FVector DirectionToMove = FVector::ZeroVector;
};