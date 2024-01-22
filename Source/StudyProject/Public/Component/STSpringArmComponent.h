// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "STSpringArmComponent.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USTSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float CameraTopAngle;

	UPROPERTY(EditAnywhere)
	float CmeraTopRadius;

	UPROPERTY(EditAnywhere)
	float CameraBottomAngle;

	UPROPERTY(EditAnywhere)
	float floatCameraBottomRadius;
	
};
