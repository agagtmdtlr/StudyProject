// Fill out your copyright notice in the Description page of Project Settings.


#include "STAIController.h"
#include "NavigationSystem.h"

ASTAIController::ASTAIController()
{
	RepeatInterval = 3.0f;
}

void ASTAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ASTAIController::OnRepeatTimer, RepeatInterval, true);
}

void ASTAIController::UnPossess()
{
	Super::UnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void ASTAIController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();
	STCHECK(CurrentPawn != nullptr);

	//UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

}
