// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "STInputConfig.generated.h"



class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FSTInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> InputAction = nullptr;

};




/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USTInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	USTInputConfig();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSTInputAction> InputActions;
	
};
