// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsKeyValueTrue.generated.h"

/**
 *
 */
UCLASS()
class UBTDecorator_IsKeyValueTrue : public UBTDecorator
{
	GENERATED_BODY()

		UBTDecorator_IsKeyValueTrue();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector BlackboardKey;
};
