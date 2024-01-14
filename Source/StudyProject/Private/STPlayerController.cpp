// Fill out your copyright notice in the Description page of Project Settings.

#include "STPlayerController.h"
#include "StudyProject.h"

void ASTPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//STLOG_S(Warning);
}

void ASTPlayerController::OnPossess(APawn* aPawn)
{
	//STLOG_S(Warning);
	Super::OnPossess(aPawn);
}

void ASTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

