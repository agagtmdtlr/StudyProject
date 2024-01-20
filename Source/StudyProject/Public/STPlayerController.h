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

	void ChangeInputMode(bool bGameMode = true);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class USTHUDWidget> HUDWidgetClass;

	UFUNCTION(BlueprintCallable)
	void OnGamePause();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=UI)
	TSubclassOf<class USTGameplayWidget> MenuWidgetClass;

private:
	UPROPERTY()
	class USTHUDWidget* HUDWidget;

	UPROPERTY()
	class ASTPlayerState* STPlayerState; //

	UPROPERTY()
	class USTGameplayWidget* MenuWidget;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;

};
