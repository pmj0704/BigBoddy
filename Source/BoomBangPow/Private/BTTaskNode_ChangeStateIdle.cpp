#include "BTTaskNode_ChangeStateIdle.h"
#include "EnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_ChangeStateIdle::UBTTaskNode_ChangeStateIdle()
{
	NodeName = L"ChangeState";
}

EBTNodeResult::Type UBTTaskNode_ChangeStateIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAI* AIController = Cast<AEnemyAI>(OwnerComp.GetAIOwner());
	AIController->mState = changeState;
	return EBTNodeResult::Succeeded;
}