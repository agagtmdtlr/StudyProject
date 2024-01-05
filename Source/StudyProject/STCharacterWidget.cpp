// Fill out your copyright notice in the Description page of Project Settings.


#include "STCharacterWidget.h"
#include "STCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void USTCharacterWidget::BindCharacterStat(USTCharacterStatComponent* NewCharacterStat)
{
	STCHECK(NewCharacterStat != nullptr);

	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddLambda([this]() -> void {
		if (CurrentCharacterStat.IsValid())
		{
			STLOG(Warning, TEXT("HP Ratio : (%f)"), CurrentCharacterStat->GetHPRatio());
		}
		});

	NewCharacterStat->OnHPChanged.AddUObject(this, &USTCharacterWidget::UpdateHPWidget);

}

void USTCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	STCHECK(HPProgressBar != nullptr);
	UpdateHPWidget();
}

void USTCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (HPProgressBar != nullptr)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}
