// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Shooter.generated.h"

class ASTGun;
class USTCharacterMovementComponent;
class USTCharacterStatComponent;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionInstance;



UCLASS()
class STUDYPROJECT_API AShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable)
	void OnCharacterMovement(const FVector2D& MovementValue);
public:
	UFUNCTION(BlueprintCallable)
	void OnCameraMovement(const FVector2D& MovementValue);
private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Camera|Rotation" , meta=(ClampMin="0", ClampMax="1",  UIMin="0", UIMax="1"))
	float CameraPitchSpeed = 1;

	UPROPERTY(EditAnywhere, Category = "Camera|Rotation", meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))
	float CameraYawSpeed = 1;

private:
	
	UPROPERTY(VisibleAnywhere, Category=Weapon)
	ASTGun* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	USTCharacterStatComponent* CharacterStat;


};
