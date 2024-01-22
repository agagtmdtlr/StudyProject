// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "STPawn.generated.h"

class UCapsuleComponent;
class UFloatingPawnMovement;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class STUDYPROJECT_API ASTPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASTPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PawnClientRestart() override;


	UPROPERTY(VisibleAnywhere, Category=Collision)
	TObjectPtr<UCapsuleComponent> _capsule;

	UPROPERTY(VisibleAnywhere, Category=Visual)
	TObjectPtr<USkeletalMeshComponent> _mesh;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	TObjectPtr<UFloatingPawnMovement> _movement;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	TObjectPtr<USpringArmComponent> _springArm;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	TObjectPtr<UCameraComponent> _camera;

	UPROPERTY(VisibleAnywhere, Category=Input)
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> MappingContext;

private:
	void ScrollMovement(const struct FInputActionValue& ActionValue);


};
