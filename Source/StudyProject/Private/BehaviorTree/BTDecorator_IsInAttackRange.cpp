// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTDecorator_IsInAttackRange.h"
#include "Controller/STAIController.h"
#include "Actor/STCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ASTCharacter* ControllingPawn = Cast<ASTCharacter>( OwnerComp.GetAIOwner()->GetPawn() );
	if (ControllingPawn == nullptr)
		return false;

	ASTCharacter* Target = Cast<ASTCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASTAIController::TargetKey));
	if (Target == nullptr)
		return false;

	// TODO:: Get ControllingPawn->GetAttackRange();
	
	const float AttackRange = ControllingPawn->GetFinalAttackRange();

	bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRange);
	return bResult;
}
