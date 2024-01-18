// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StudyProject.h"
#include "Blueprint/UserWidget.h"
#include "STCharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USTCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	void NextCharacter(bool bForward = true);

	// Initailize time
	virtual void NativeConstruct() override; 

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	int32 CurrentIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Character)
	int32 MaxIndex;

	TWeakObjectPtr<USkeletalMeshComponent> TargetComponent;

	UPROPERTY()
	class UButton* PrevButton;

	UPROPERTY()
	class UButton* NextButton;

	UPROPERTY()
	class UEditableTextBox* TextBox;

	UPROPERTY()
	class UButton* ConfirmButton;

private:
	UFUNCTION()
	void OnPrevClicked();

	UFUNCTION()
	void OnNextClicked();

	UFUNCTION()
	void OnConfirmClicked();
};
