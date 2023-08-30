// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h" // SpringArmComponent를 사용하려면 포함해야 합니다.
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
// 생성한 C++ 클래스의 구현 파일

AMyPlayerCameraManager::AMyPlayerCameraManager()
{
    // 기본 RootComponent 생성
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Spring Arm Component 생성
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 300.0f; // 카메라 거리
    SpringArmComponent->bUsePawnControlRotation = true; // 캐릭터 회전과 함께 카메라 회전

    // 카메라 컴포넌트 생성 및 붙이기
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void AMyPlayerCameraManager::BeginPlay()
{
    Super::BeginPlay();

    // 플레이어 컨트롤러 찾기
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

    if (PlayerController)
    {
        // 플레이어 컨트롤러의 포커스 대상(플레이어 캐릭터)를 카메라 포커스 대상으로 설정
        PlayerController->SetViewTargetWithBlend(this);
    }
}