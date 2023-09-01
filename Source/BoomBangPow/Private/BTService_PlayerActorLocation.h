// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAI.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTService.h"
#include "BTService_PlayerActorLocation.generated.h"

UCLASS()
class UBTService_PlayerActorLocation : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_PlayerActorLocation();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
