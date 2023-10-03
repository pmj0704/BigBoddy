// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CombatMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_CombatMoveTo : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTask_CombatMoveTo();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
