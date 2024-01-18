// Fill out your copyright notice in the Description page of Project Settings.


#include "STUIPlayerController.h"
#include "Blueprint/UserWidget.h"

void ASTUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	STCHECK(UIWidgetClass != nullptr);

	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	STCHECK(UIWidgetInstance != nullptr);

	UIWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}
