// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BTNode/BTService_CheckDistanceService.h"

UBTService_CheckDistanceService::UBTService_CheckDistanceService()
{
	NodeName = "Check Distance";
}

void UBTService_CheckDistanceService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (!AIController) return;

	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn) return;

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAI::Key_PlayerActor));
	if (!TargetActor) return;

	float SquaredDistance = FVector::DistSquared(AIPawn->GetActorLocation(), TargetActor->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), SquaredDistance);

	float MaxDistanceSquared = FMath::Square(distance);

	UE_LOG(LogTemp, Warning, TEXT("Key: %s, Bool: %s"), *BlackboardKey.SelectedKeyName.ToString(), SquaredDistance <= MaxDistanceSquared ? TEXT("TRUE") : TEXT("FALSE"));
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BlackboardKey.SelectedKeyName, SquaredDistance <= MaxDistanceSquared);
}
