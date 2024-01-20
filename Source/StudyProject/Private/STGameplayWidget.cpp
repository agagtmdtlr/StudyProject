// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameplayWidget.h"
#include "Components/Button.h"

void USTGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
	if (ResumeButton != nullptr)
	{
		ResumeButton->OnClicked.AddDynamic(this, &USTGameplayWidget::OnResumeClikced);
	}

	ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
	if (ReturnToTitleButton != nullptr)
	{
		ReturnToTitleButton->OnClicked.AddDynamic(this, &USTGameplayWidget::OnReturnToTitleClicked);
	}

	RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
	if (RetryGameButton != nullptr)
	{
		RetryGameButton->OnClicked.AddDynamic(this, &USTGameplayWidget::OnRetryGameClicked);
	}

}

void USTGameplayWidget::OnResumeClikced()
{

}

void USTGameplayWidget::OnReturnToTitleClicked()
{
}

void USTGameplayWidget::OnRetryGameClicked()
{
}
