// Fill out your copyright notice in the Description page of Project Settings.


#include "STAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ASTAIController::HomePosKey(TEXT("HomePos"));
const FName ASTAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ASTAIController::TargetKey(TEXT("Target"));


ASTAIController::ASTAIController()
{
	RepeatInterval = 3.0f;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_STCharacter.BB_STCharacter"));
	if (BBObject.Succeeded())
		BBAsset = BBObject.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_STCharacter.BT_STCharacter"));
	if (BTObject.Succeeded())
		BTAsset = BTObject.Object;

}

void ASTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ASTAIController::OnRepeatTimer, RepeatInterval, true);

	UBlackboardComponent* BBComponent = GetBlackboardComponent();
	if (UseBlackboard(BBAsset, BBComponent))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			STLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}

}


void ASTAIController::OnUnPossess()
{
	Super::OnUnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}


void ASTAIController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();
	STCHECK(CurrentPawn != nullptr);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	STCHECK(NavSystem != nullptr);

	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
		STLOG(Warning, TEXT("Next Location : %s"), *NextLocation.Location.ToString());
	}

}
