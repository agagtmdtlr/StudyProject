// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h" // Ascyn Load
#include "STGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSTCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSTCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float MaxHP;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	//float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int32 NextExp;

};



/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USTGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USTGameInstance();

	virtual void Init() override;
	FSTCharacterData* GetSTCharacterData(int32 Level);

	FStreamableManager StreamableManager;

private:
	UPROPERTY()
	class UDataTable* STCharacterTable;


};
