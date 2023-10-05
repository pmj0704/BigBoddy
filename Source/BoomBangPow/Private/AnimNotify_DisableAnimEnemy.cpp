// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_DisableAnimEnemy.h"
#include "EnemyCharacter.h"

void UAnimNotify_DisableAnimEnemy::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    AActor* OwnerActor = MeshComp->GetOwner();

    // OwnerActor가 ACharacter 클래스의 인스턴스인지 확인합니다.
    AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerActor);

    if(Character) Character->canAnim = true;
}
