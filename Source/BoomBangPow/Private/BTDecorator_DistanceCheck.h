#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_DistanceCheck.generated.h"

UCLASS()
class UBTDecorator_DistanceCheck : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_DistanceCheck();

	UPROPERTY(Category = Node, EditAnywhere, meta = (ClampMin = "0.0"))
	float distance = 300;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
};
