// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAI.h"
#include "AIController.h"
#include "BTNode/BTDecorator_IsKeyValueTrue.h"

UBTDecorator_IsKeyValueTrue::UBTDecorator_IsKeyValueTrue()
{
	NodeName = "IsKeyValue";
}

bool UBTDecorator_IsKeyValueTrue::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//UE_LOG(LogTemp, Warning, TEXT("KEY: %s"), *BlackboardKey.SelectedKeyName.ToString());
	bool result = OwnerComp.GetBlackboardComponent()->GetValueAsBool(BlackboardKey.SelectedKeyName);
	return result;
}
