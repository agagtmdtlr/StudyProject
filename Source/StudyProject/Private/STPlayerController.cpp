// Fill out your copyright notice in the Description page of Project Settings.

#include "STPlayerController.h"
#include "STHUDWidget.h"
#include "STPlayerState.h"
#include "STCharacter.h"
#include "STGameplayWidget.h"

ASTPlayerController::ASTPlayerController()
{

	/// Script / UMGEditor.WidgetBlueprint'/Game/UI/UI_HUD.UI_HUD'
	static ConstructorHelpers::FClassFinder<USTHUDWidget> UI_HUD_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	/// Script / UMGEditor.WidgetBlueprint'/Game/UI/UI_Menu.UI_Menu'
	static ConstructorHelpers::FClassFinder<USTGameplayWidget> UI_Menu_C(TEXT("/Game/UI/UI_Menu.UI_Menu_C"));
	if (UI_Menu_C.Succeeded())
	{
		MenuWidgetClass = UI_Menu_C.Class;
	}

}

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

void ASTPlayerController::SetPlayer(UPlayer* InPlayer)
{
	Super::SetPlayer(InPlayer);

}

void ASTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	HUDWidget = CreateWidget<USTHUDWidget>(this, HUDWidgetClass);
	STCHECK(HUDWidget != nullptr);
	HUDWidget->AddToViewport(1);

	STPlayerState = Cast<ASTPlayerState>(PlayerState);
	STCHECK(STPlayerState != nullptr);
	HUDWidget->BindPlayerState(STPlayerState);
	STPlayerState->OnPlayerStateChanged.Broadcast();

}

void ASTPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<USTGameplayWidget>(this, MenuWidgetClass);
	STCHECK(MenuWidget != nullptr);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
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

void ASTPlayerController::ChangeInputMode(bool bGameMode /*= true*/)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

