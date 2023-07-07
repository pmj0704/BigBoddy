// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyFSM.h"
#include "TPSCharacter.h"
#include "Enemy.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ���忡�� ATPSPlayer Ÿ�� ã�ƿ���
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATPSCharacter::StaticClass());
	// ATPSPlayer Ÿ������ ĳ����
	target = Cast<ATPSCharacter>(actor);
	 //���� ��ü ��������
	me = Cast<AEnemy>(GetOwner());
	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (mState)
	{
	case EEnemyState::Idle:
		break;
	case EEnemyState::Chat:
		break;
	case EEnemyState::Patrol:
		break;
	case EEnemyState::Move:
		break;
	case EEnemyState::Attack:
		break;
	case EEnemyState::Damage:
		break;
	case EEnemyState::Die:
		break;
	}
}

void UEnemyFSM::IdleState()
{
	// �ð��� �巯
	currentTime += GetWorld()->DeltaTimeSeconds;
	// ����ð��� ��� �ð��� �ʰ� �ߴٸ�
	if (currentTime > idleDelayTime)
	{
		// �̵� ���·� ��ȯ �Ѵ�
		mState = EEnemyState::Move;
		currentTime = 0;
	}
}

void UEnemyFSM::ChatSate()
{
}

void UEnemyFSM::PatrolState()
{
}

void UEnemyFSM::MoveState()
{
	// Ÿ�� ������
	FVector dest = target->GetActorLocation();
	// ����
	FVector dir = dest - me->GetActorLocation();
	// �������� �̵�
	me->AddMovementInput(dir.GetSafeNormal());
}

void UEnemyFSM::AttackState()
{
}

void UEnemyFSM::DamageState()
{
}

void UEnemyFSM::DieState()
{
}

