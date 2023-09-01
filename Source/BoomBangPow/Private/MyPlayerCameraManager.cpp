// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h" // SpringArmComponent�� ����Ϸ��� �����ؾ� �մϴ�.
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
// ������ C++ Ŭ������ ���� ����

AMyPlayerCameraManager::AMyPlayerCameraManager()
{
    // �⺻ RootComponent ����
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Spring Arm Component ����
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 300.0f; // ī�޶� �Ÿ�
    SpringArmComponent->bUsePawnControlRotation = true; // ĳ���� ȸ���� �Բ� ī�޶� ȸ��

    // ī�޶� ������Ʈ ���� �� ���̱�
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void AMyPlayerCameraManager::BeginPlay()
{
    Super::BeginPlay();

    // �÷��̾� ��Ʈ�ѷ� ã��
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

    if (PlayerController)
    {
        // �÷��̾� ��Ʈ�ѷ��� ��Ŀ�� ���(�÷��̾� ĳ����)�� ī�޶� ��Ŀ�� ������� ����
        PlayerController->SetViewTargetWithBlend(this);
    }
}