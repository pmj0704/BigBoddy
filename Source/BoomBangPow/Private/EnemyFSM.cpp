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

	// 월드에서 ATPSPlayer 타겟 찾아오기
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATPSCharacter::StaticClass());
	// ATPSPlayer 타입으로 캐스팅
	target = Cast<ATPSCharacter>(actor);
	 //소유 객체 가져오기
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
	// 시간이 흐러
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 경과시간이 대기 시간을 초과 했다면
	if (currentTime > idleDelayTime)
	{
		// 이동 상태로 전환 한다
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
	// 타겟 목적지
	FVector dest = target->GetActorLocation();
	// 방향
	FVector dir = dest - me->GetActorLocation();
	// 방향으로 이동
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

