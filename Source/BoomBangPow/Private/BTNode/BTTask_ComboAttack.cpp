// Fill out your copyright notice in the Description page of Project Settings.

#include "BTNode/BTTask_ComboAttack.h"
#include "EnemyAI.h"
#include "EnemyCharacter.h"

UBTTask_ComboAttack::UBTTask_ComboAttack()
{
	NodeName = TEXT("Destroy");
}

EBTNodeResult::Type UBTTask_ComboAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (!AIController) 	return EBTNodeResult::Failed;

	APawn* ControlledPawn = AIController->GetPawn();
	AEnemyCharacter* ControlledCharacter = Cast<AEnemyCharacter>(ControlledPawn);

	ControlledCharacter->DestroyActor();
	return EBTNodeResult::Succeeded;
}

