// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckStun.generated.h"

UCLASS()
class UBTDecorator_CheckStun : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckStun();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
