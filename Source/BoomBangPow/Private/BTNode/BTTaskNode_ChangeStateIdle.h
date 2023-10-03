#pragma once

#include "EnemyAI.h"
#include "EnemyCharacter.h"
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_ChangeStateIdle.generated.h"

UCLASS()
class UBTTaskNode_ChangeStateIdle : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_ChangeStateIdle();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(Category = Node, EditAnywhere, meta = (ClampMin = "0.0"))
	EEnemyState changeState;
};
