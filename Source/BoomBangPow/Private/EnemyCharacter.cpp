// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "GameFramework/Character.h" // ACharacter 클래스를 사용하기 위한 헤더
#include "GameFramework/CharacterMovementComponent.h" // UCharacterMovementComponent를 사용하기 위한 헤더
#include "EnemyAI.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "EnemyComboAttackData.h"
#include "Engine/DamageEvents.h"


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
		ChangeSpeed(0.0f);
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

void AEnemyCharacter::DestroyActor()
{
	Super::Destroy();
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	hp -= damage;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (hp <= 0)
	{
		AnimInstance->StopAllMontages(0.0f);
		mState = EEnemyState::Dead;
		AnimInstance->Montage_Play(DieMontage, 1.0f);
	}
	else
	{
		mState = EEnemyState::Stun;
		UE_LOG(LogTemp, Log, TEXT("%s", mState));
		AnimInstance->StopAllMontages(0.0f);
	}
	return DamageAmount;
}

void AEnemyCharacter::AttackHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Parmas(SCENE_QUERY_STAT(Attack), false, this);


	const float AttackRange = 40.0f;
	const float AttackRadius = 50.0f;
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();

	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(AttackRadius), Parmas);

	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(damage, DamageEvent, GetController(), this);
	}
#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 5.0f);


#endif // ENABLE_DRAW_DEBUG
}