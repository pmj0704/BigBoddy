#include "BTDecorator_CheckStun.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"

UBTDecorator_CheckStun::UBTDecorator_CheckStun()
{
	NodeName = L"Check Stun";
}

bool UBTDecorator_CheckStun::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyAI* AIController = Cast<AEnemyAI>(OwnerComp.GetAIOwner());
	bool bState = (AIController->GetEnemyState() == checkState);
	return bState;
}
