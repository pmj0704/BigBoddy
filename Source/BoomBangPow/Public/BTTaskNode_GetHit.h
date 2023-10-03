// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_GetHit.generated.h"

/**
 * 
 */
UCLASS()
class BOOMBANGPOW_API UBTTaskNode_GetHit : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	AEnemyCharacter* OwnerCharacter;
};
