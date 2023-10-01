// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

const FName AEnemyAI::Key_DefaultPos(TEXT("DefaultPos"));
const FName AEnemyAI::Key_PatrolPos(TEXT("PatrolPos"));
const FName AEnemyAI::Key_PlayerActor(TEXT("PlayerActor"));
const FName AEnemyAI::Key_PlayerActorPos(TEXT("PlayerActorPos"));
const FName AEnemyAI::Key_StateMode(TEXT("Mode"));

AEnemyAI::AEnemyAI()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Script/AIModule.BlackboardData'/Game/BBP_Contents/Enemy/BBEnemy.BBEnemy''"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Script/AIModule.BehaviorTree'/Game/BBP_Contents/Enemy/BTEnemy.BTEnemy''"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
	BlackboardComp = Blackboard;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(L"PerceptionComp");

	// �ð� ���� (Sight Sense) ���� ����
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(L"Sight");
	SightConfig->SightRadius = SightDistance; // �ð� ���� �ݰ� (���ϴ� ũ��� ����)
	SightConfig->LoseSightRadius = SightConfig->SightRadius; // �þ� �ս� �ݰ� (���ϴ� ũ��� ����)
	SightConfig->DetectionByAffiliation.bDetectEnemies = true; // �� ����
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true; // �߸� ����
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false; // �Ʊ� ���� (������)
	SightConfig->PeripheralVisionAngleDegrees = 360.0f; // �þ� ������ 90���� ���� (���ϴ� ������ ����)

	//// ������ ������ AI Perception ������Ʈ�� �߰�
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();	

	//ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//GetBlackboardComponent()->SetValueAsObject(Key_PlayerActor, player);
	OwnerPawn = Cast<AEnemyCharacter>(GetPawn());

	//// OnPerceptionUpdated �̺�Ʈ�� ���� �ڵ鷯 ���
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyAI::OnPerceptionUpdated);

	//// AIPerceptionComponent�� Ȱ��ȭ
	AIPerceptionComponent->Activate();
}

void AEnemyAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void AEnemyAI::RunAI()
{
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		RunBehaviorTree(BTAsset);
	}
}

void AEnemyAI::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}


void AEnemyAI::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (auto var : UpdatedActors)
	{
		CheckSightPlayer(var);
	}
}

void AEnemyAI::CheckSightPlayer(AActor* SightActor)
{
	for (FName var : SightActor->Tags)
	{
		FString TagString = var.ToString(); // FName�� FString���� ��ȯ
		UE_LOG(LogTemp, Warning, TEXT("UpdatedActor's Tag: %s"), *TagString);
	}

	if (SightActor->ActorHasTag("Player"))
	{
		UE_LOG(LogTemp, Warning, TEXT("UpdatedActor's Name: %s"), *SightActor->GetName());
		if (IsValid(GetBlackboardComponent()->GetValueAsObject(Key_PlayerActor)))
		{
			GetBlackboardComponent()->SetValueAsObject(Key_PlayerActor, nullptr);
		}
		else
		{
			GetBlackboardComponent()->SetValueAsObject(Key_PlayerActor, SightActor);
		}
	}
}

EEnemyState AEnemyAI::GetEnemyState()
{
	return OwnerPawn->mState;
}

void AEnemyAI::SetEnemyState(EEnemyState setState)
{
	OwnerPawn->mState = setState;
}