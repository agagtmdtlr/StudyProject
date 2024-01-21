// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameplayResultWidget.h"

#include "Components/TextBlock.h"
#include "STGameState.h"

void USTGameplayResultWidget::BindGameState(class ASTGameState* GameState)
{
	STCHECK(GameState != nullptr);
	CurrentGameState = GameState;
}

// Call when called widget->AddToViewport();
void USTGameplayResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	STCHECK(CurrentGameState.IsValid());

	auto Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtResult")));
	STCHECK(Result != nullptr);
	Result->SetText(FText::FromString(CurrentGameState->IsGameCleared() ? TEXT("Mission Completed") : TEXT("Mission Failed")));

	auto TotalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txxtTotalScore")));
	STCHECK(TotalScore != nullptr);
	TotalScore->SetText(FText::FromString(FString::FromInt(CurrentGameState->GetTotalGameScore())));
}
