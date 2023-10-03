// Fill out your copyright notice in the Description page of Project Settings.


#include "BTNode/BTTask_CombatMoveTo.h"
#include "EnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "NavigationSystem.h"


UBTTask_CombatMoveTo::UBTTask_CombatMoveTo()
{

}

EBTNodeResult::Type UBTTask_CombatMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Get the AI controller and the blackboard component
    AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    AEnemyAI* EnemyAIController = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

    if (AIController && BlackboardComp && EnemyAIController)
    {
        // Get the target player actor's position from the blackboard
        AActor* PlayerActor = Cast<AActor>(BlackboardComp->GetValueAsObject(AEnemyAI::Key_PlayerActor));
        EnemyAIController->SetEnemyState(EEnemyState::Combat);

        if (PlayerActor)
        {
            // Get the target position (player actor's position)
            FVector TargetPosition = PlayerActor->GetActorLocation();

            // Check if navigation is possible to the target position
            UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
            if (NavSystem)
            {
                // Check if the AI can reach the target position
                if (AIController->MoveToLocation(TargetPosition))
                {
                    // Successfully started moving towards the target position
                    return EBTNodeResult::InProgress;
                }
            }
        }
    }

    // If anything fails, return failure
    return EBTNodeResult::Failed;
}
