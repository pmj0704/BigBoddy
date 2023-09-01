// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "EnemyAI.generated.h"

// 사용할 상태 정의
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Stun,
	Combat
};

UCLASS()
class AEnemyAI : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAI();
	virtual void OnPossess(APawn* InPawn) override;
	
	static const FName Key_DefaultPos;
	static const FName Key_PatrolPos;
	static const FName Key_PlayerActor;
	static const FName Key_PlayerActorPos;
	static const FName Key_StateMode;

	void RunAI();
	void StopAI();

	UPROPERTY(Category = State, EditAnywhere, meta = (ClampMin = "0.0"))
	EEnemyState mState = EEnemyState::Idle;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;

	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

public:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void CheckSightPlayer(AActor* SightActor);
};
