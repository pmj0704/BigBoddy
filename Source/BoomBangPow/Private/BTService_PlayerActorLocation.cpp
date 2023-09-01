// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerActorLocation.h"
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
    }
}

UBTService_PlayerActorLocation::UBTService_PlayerActorLocation()
{

}
