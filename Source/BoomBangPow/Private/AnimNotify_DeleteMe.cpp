// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_DeleteMe.h"
#include "EnemyCharacter.h"

void UAnimNotify_DeleteMe::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AEnemyCharacter* enemyCharacter = Cast<AEnemyCharacter>(MeshComp->GetOwner());
	enemyCharacter->DisableMovement();
}
