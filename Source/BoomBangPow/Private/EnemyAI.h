// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class AEnemyAI : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAI();
	virtual void OnPossess(APawn* InPawn) override;
	
	static const FName Key_DefaultPos;
	static const FName Key_PatrolPos;

	void RunAI();
	void StopAI();

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
