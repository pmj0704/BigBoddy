// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerActorLocation.h"
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
    }
}

UBTService_PlayerActorLocation::UBTService_PlayerActorLocation()
{

}
