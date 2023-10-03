// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTService_CheckDistanceService.generated.h"

/**
 * 
 */
UCLASS()
class UBTService_CheckDistanceService : public UBTService
{
	GENERATED_BODY()

	UBTService_CheckDistanceService();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY(Category = Node, EditAnywhere, meta = (ClampMin = "0.0"))
	float distance = 300;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector BlackboardKey;
};
