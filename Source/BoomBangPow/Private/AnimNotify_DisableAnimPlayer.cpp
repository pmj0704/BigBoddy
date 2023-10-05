// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_DisableAnimPlayer.h"
#include "Character/CharacterPlayer.h"

void UAnimNotify_DisableAnimPlayer::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    // ���� ���͸� ����ϴ�.
    AActor* OwnerActor = MeshComp->GetOwner();

    // OwnerActor�� ACharacter Ŭ������ �ν��Ͻ����� Ȯ���մϴ�.
    ACharacterPlayer* Character = Cast<ACharacterPlayer>(OwnerActor);

    if (Character)
    {
        Character->canAnim = true;
        Character->ReturnWalking();
    }
}
