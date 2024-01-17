// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "GameFramework/PlayerController.h"
#include "STPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API ASTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASTPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	
	virtual void SetPlayer(UPlayer* InPlayer) override;


	class USTHUDWidget* GetHUDWidget() const;
	void NPCKill(class ASTCharacter* KilledNPC) const;
	void AddGameScore() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class USTHUDWidget> HUDWidgetClass;

private:
	UPROPERTY()
	class USTHUDWidget* HUDWidget;


	UPROPERTY()
	class ASTPlayerState* STPlayerState; //
};
