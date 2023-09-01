#include "BTDecorator_DistanceCheck.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAI.h"
#include "AIController.h"
#include "GameFramework/Actor.h"

UBTDecorator_DistanceCheck::UBTDecorator_DistanceCheck()
{
	NodeName = "Distance Check";
}

bool UBTDecorator_DistanceCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
    {
        return false;
    }

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        return false;
    }

    AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAI::Key_PlayerActor));
    if (!TargetActor)
    {
        return false;
    }

    float SquaredDistance = FVector::DistSquared(AIPawn->GetActorLocation(), TargetActor->GetActorLocation());

    float MaxDistanceSquared = FMath::Square(distance);
    return SquaredDistance <= MaxDistanceSquared;
}
