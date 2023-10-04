// Fill out your copyright notice in the Description page of Project Settings.

#include "BTNode/BTTask_MoveToByCondition.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_MoveToByCondition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsCombatDistance")))
	{
		return EBTNodeResult::Failed;
	}

	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsAttackDistance")))
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTTask_MoveToByCondition::PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::PerformMoveTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsCombatDistance")))
	{
		return EBTNodeResult::Failed;
	}

	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsAttackDistance")))
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Succeeded;
}
