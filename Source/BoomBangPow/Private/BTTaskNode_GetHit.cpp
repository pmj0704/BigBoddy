// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_GetHit.h"
#include "EnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyCharacter.h"
#include "Animation/AnimMontage.h"

EBTNodeResult::Type UBTTaskNode_GetHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Succeeded;
}
