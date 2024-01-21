// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameplayWidget.h"
#include "Components/Button.h"
#include "STPlayerController.h"

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
	auto STPlayerController = Cast<ASTPlayerController>(GetOwningPlayer());
	STCHECK(STPlayerController != nullptr);

	RemoveFromParent();

	STPlayerController->ChangeInputMode(true);
	STPlayerController->SetPause(false);
}

void USTGameplayWidget::OnReturnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void USTGameplayWidget::OnRetryGameClicked()
{
	auto STPlayerController = Cast<ASTPlayerController>(GetOwningPlayer());
	STCHECK(STPlayerController != nullptr);

	STPlayerController->RestartLevel();
}
