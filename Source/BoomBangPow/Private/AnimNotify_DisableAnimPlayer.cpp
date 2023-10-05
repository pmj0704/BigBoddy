// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_DisableAnimPlayer.h"
#include "Character/CharacterPlayer.h"

void UAnimNotify_DisableAnimPlayer::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    // 현재 액터를 얻습니다.
    AActor* OwnerActor = MeshComp->GetOwner();

    // OwnerActor가 ACharacter 클래스의 인스턴스인지 확인합니다.
    ACharacterPlayer* Character = Cast<ACharacterPlayer>(OwnerActor);

    if (Character)
    {
        Character->canAnim = true;
        Character->ReturnWalking();
    }
}
