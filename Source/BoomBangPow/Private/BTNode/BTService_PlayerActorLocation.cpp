// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerActorLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyAI.h"

void UBTService_PlayerActorLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Blackboard ������Ʈ
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (BlackboardComp)
    {
        // PlayerActorKey Ű�κ��� Actor ���� ������
        AActor* PlayerActor = Cast<AActor>(BlackboardComp->GetValueAsObject(AEnemyAI::Key_PlayerActor));

        if (IsValid(PlayerActor))
        {
            // ��ȿ�� Actor�� ��� Actor�� ��ġ�� �����ͼ� ����.
            FVector PlayerLocation = PlayerActor->GetActorLocation();
            BlackboardComp->SetValueAsVector(AEnemyAI::Key_PlayerActorPos, PlayerLocation);
        }

        bool bCurrentValue = BlackboardComp->GetValueAsBool(L"IsCombatDistance");

        if (!bInitialized)
        {
            bPreviousValue = bCurrentValue;
            bInitialized = true;
        }

        // ���� ���� ���� ���� �ٸ��� �۾��� ���� ó���մϴ�.
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

        // ���� ���� ���� ���� �ٸ��� �۾��� ���� ó���մϴ�.
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
