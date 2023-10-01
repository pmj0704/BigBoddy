// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerActorLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyAI.h"

void UBTService_PlayerActorLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Blackboard 컴포넌트
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (BlackboardComp)
    {
        // PlayerActorKey 키로부터 Actor 값을 가져옴
        AActor* PlayerActor = Cast<AActor>(BlackboardComp->GetValueAsObject(AEnemyAI::Key_PlayerActor));

        if (IsValid(PlayerActor))
        {
            // 유효한 Actor인 경우 Actor의 위치를 가져와서 저장.
            FVector PlayerLocation = PlayerActor->GetActorLocation();
            BlackboardComp->SetValueAsVector(AEnemyAI::Key_PlayerActorPos, PlayerLocation);
        }

        bool bCurrentValue = BlackboardComp->GetValueAsBool(L"IsCombatDistance");

        if (!bInitialized)
        {
            bPreviousValue = bCurrentValue;
            bInitialized = true;
        }

        // 이전 값과 현재 값이 다르면 작업을 실패 처리합니다.
        if (bPreviousValue != bCurrentValue)
        {
            if (BlackboardComp->GetValueAsBool(L"IsCombatDistance"))
            {
                OwnerComp.RequestExecution(EBTNodeResult::Type::Failed);
            }
        }

        bPreviousValue = bCurrentValue;

        bool bCurrentValue1 = BlackboardComp->GetValueAsBool(L"IsAttackDistance");

        if (!bInitialized1)
        {
            bPreviousValue1 = bCurrentValue1;
            bInitialized1 = true;
        }

        // 이전 값과 현재 값이 다르면 작업을 실패 처리합니다.
        if (bPreviousValue1 != bCurrentValue1)
        {
            if (BlackboardComp->GetValueAsBool(L"IsAttackDistance"))
            {
                OwnerComp.RequestExecution(EBTNodeResult::Type::Failed);
            }
        }

        bPreviousValue1 = bCurrentValue1;
    }

}



UBTService_PlayerActorLocation::UBTService_PlayerActorLocation()
{
    
}
