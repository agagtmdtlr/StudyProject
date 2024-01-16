// Fill out your copyright notice in the Description page of Project Settings.


#include "STHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "STCharacterStatComponent.h"
#include "STPlayerState.h"

void USTHUDWidget::BindCharacterStat(class USTCharacterStatComponent* CharacterStat)
{
	STCHECK(CharacterStat != nullptr);
	CurrentCharacterStat = CharacterStat;
	CharacterStat->OnHPChanged.AddUObject(this, &USTHUDWidget::UpdateCharacterStat);
}

void USTHUDWidget::BindPlayerState(ASTPlayerState* PlayerState)
{
	STCHECK(PlayerState != nullptr);
	CurrentPlayerState = PlayerState;
	PlayerState->OnPlayerStateChanged.AddUObject(this, &USTHUDWidget::UpdatePlayerState);
}

void USTHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	STCHECK(HPBar != nullptr);

	ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbEXp")));
	STCHECK(ExpBar != nullptr);

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	STCHECK(PlayerName != nullptr);

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	STCHECK(PlayerLevel != nullptr);

	CurrentScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentScore")));
	STCHECK(CurrentScore != nullptr);

	HighScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtHighScore")));
	STCHECK(HighScore != nullptr);

}

void USTHUDWidget::UpdateCharacterStat()
{
	STCHECK(CurrentCharacterStat.IsValid());

	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}

void USTHUDWidget::UpdatePlayerState()
{
	STCHECK(CurrentPlayerState.IsValid());

	PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
	PlayerLevel->SetText(FText::FromString( FString::FromInt( CurrentPlayerState->GetCharacterLevel())) );
	CurrentScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameScore())));

	ExpBar->SetPercent(CurrentPlayerState->GetExpRatio());

}
