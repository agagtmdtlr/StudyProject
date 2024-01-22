// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTask_Attack.h"
#include "Controller/STAIController.h"
#include "Actor/STCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ASTCharacter* STCharacter = Cast<ASTCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (STCharacter == nullptr)
		return EBTNodeResult::Failed;


	// if end action of attack then call OnAttackEnd
	STCharacter->Attack();
	IsAttacking = true;
	STCharacter->OnAttackEnd.AddLambda([this]()->void {IsAttacking = false; });

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
