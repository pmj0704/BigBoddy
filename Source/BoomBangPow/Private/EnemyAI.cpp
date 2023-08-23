// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName AEnemyAI::Key_DefaultPos(TEXT("DefaultPos"));
const FName AEnemyAI::Key_PatrolPos(TEXT("PatrolPos"));

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

}

void AEnemyAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void AEnemyAI::RunAI()
{
	UBlackboardComponent* BlackboardComp = Blackboard;
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
