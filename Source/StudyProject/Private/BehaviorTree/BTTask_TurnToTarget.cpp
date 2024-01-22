// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTask_TurnToTarget.h"
#include "Controller/STAIController.h"
#include "Actor/STCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ASTCharacter* STCharcter = Cast<ASTCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (STCharcter == nullptr)
		return EBTNodeResult::Failed;

	ASTCharacter* Target = Cast<ASTCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASTAIController::TargetKey));
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - STCharcter->GetActorLocation();
	LookVector.Z = 0.0f; // planar to xy plane.
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	STCharcter->SetActorRotation(FMath::RInterpTo(STCharcter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
