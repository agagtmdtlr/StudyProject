// Fill out your copyright notice in the Description page of Project Settings.

#include "STPlayerController.h"
#include "STHUDWidget.h"
#include "STPlayerState.h"
#include "STCharacter.h"

ASTPlayerController::ASTPlayerController()
{

	/// Script / UMGEditor.WidgetBlueprint'/Game/UI/UI_HUD.UI_HUD'
	static ConstructorHelpers::FClassFinder<USTHUDWidget> UI_HUD_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;

	}
}

void ASTPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HUDWidget = CreateWidget<USTHUDWidget>(this, HUDWidgetClass);
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

	HUDWidget->AddToViewport();

	STPlayerState = Cast<ASTPlayerState>(PlayerState);
	STCHECK(STPlayerState != nullptr);
	HUDWidget->BindPlayerState(STPlayerState);
	STPlayerState->OnPlayerStateChanged.Broadcast();

}

USTHUDWidget* ASTPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

void ASTPlayerController::NPCKill(class ASTCharacter* KilledNPC) const
{
	STPlayerState->AddExp(KilledNPC->GetExp());
}

void ASTPlayerController::AddGameScore() const
{
	STPlayerState->AddGameScore();
}

