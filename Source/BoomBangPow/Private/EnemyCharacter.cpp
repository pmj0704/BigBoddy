// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "GameFramework/Character.h" // ACharacter 클래스를 사용하기 위한 헤더
#include "GameFramework/CharacterMovementComponent.h" // UCharacterMovementComponent를 사용하기 위한 헤더
#include "EnemyAI.h"
#include "Engine/World.h"


AEnemyCharacter::AEnemyCharacter()
{
	// 스켈레탈메시 데이터 로드
	ConstructorHelpers::FObjectFinder<USkeletalMesh >
		tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/SCK_Casual01/Models/Premade_Characters/MESH_PC_01.MESH_PC_01'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
		GetMesh()->SetRelativeScale3D(FVector(0.84f));
	}

	AIControllerClass = AEnemyAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	ControlledCharacter = Cast<ACharacter>(this);
	CharacterMovement = ControlledCharacter->GetCharacterMovement();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

			if (mState == EEnemyState::Idle)
			{
				ChangeSpeed(300.0f);
			}
			if (mState == EEnemyState::Stun)
			{

			}
			if (mState == EEnemyState::Combat)
			{
				ChangeSpeed(150.0f);
			}
}

void AEnemyCharacter::ChangeSpeed(float speed)
{
	if (ControlledCharacter)
	{
		// AI 캐릭터의 이동 속도 설정
		if (CharacterMovement)
		{
			CharacterMovement->MaxWalkSpeed = speed;
		}
	}
}

void AEnemyCharacter::hitEnemy()
{
	hp -= damage;

	if (hp <= 0)
	{
		PlayAnimMontage(DieMontage);
		FTimerHandle DestroyTimerHandle;
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AEnemyCharacter::DestroyActor, 10.0f, false);
	}
	else
	{
		PlayAnimMontage(HurtMontage);
	}
}

void AEnemyCharacter::DestroyActor()
{
	Super::Destroy();
}
