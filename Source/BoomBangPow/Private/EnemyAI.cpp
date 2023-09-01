// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AEnemyAI::Key_DefaultPos(TEXT("DefaultPos"));
const FName AEnemyAI::Key_PatrolPos(TEXT("PatrolPos"));
const FName AEnemyAI::Key_PlayerActor(TEXT("PlayerActor"));
const FName AEnemyAI::Key_PlayerActorPos(TEXT("PlayerActorPos"));
const FName AEnemyAI::Key_StateMode(TEXT("Mode"));

AEnemyAI::AEnemyAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Script/AIModule.BlackboardData'/Game/BBP_Contents/Enemy/BBEnemy.BBEnemy''"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Script/AIModule.BehaviorTree'/Game/BBP_Contents/Enemy/BTEnemy.BTEnemy''"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
	BlackboardComp = Blackboard;
}

void AEnemyAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void AEnemyAI::RunAI()
{
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		RunBehaviorTree(BTAsset);
	}
}

void AEnemyAI::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}


void AEnemyAI::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (auto var : UpdatedActors)
	{
		CheckSightPlayer(var);
	}
}

void AEnemyAI::CheckSightPlayer(AActor* SightActor)
{
	if (SightActor->ActorHasTag("Player"))
	{
		if (IsValid(GetBlackboardComponent()->GetValueAsObject(Key_PlayerActor)))
		{
			GetBlackboardComponent()->SetValueAsObject(Key_PlayerActor, nullptr);
		}
		else
		{
			GetBlackboardComponent()->SetValueAsObject(Key_PlayerActor, SightActor);
		}
	}
}

