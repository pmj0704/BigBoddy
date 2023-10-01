// Fill out your copyright notice in the Description page of Project Settings.


#include "BTNode/BTTaskNode_Attack.h"
#include "EnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyComboAttackData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	NodeName = TEXT("ComboAttack");
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerCharacter = OwnerComp.GetAIOwner()->GetCharacter();

	ComboActionMontage = Cast<AEnemyCharacter>(OwnerCharacter)->ComboActionMontage;
	ComboActionData = Cast<AEnemyCharacter>(OwnerCharacter)->ComboActionData;
	UE_LOG(LogTemp, Warning, TEXT("COMBOATTACK"));
	if (CurrentCombo == 0) 
	{ 
		ComboActionBegin();
		return EBTNodeResult::Succeeded;
	}

	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
	{
		HasNextComboCommand = true;
	}

	return EBTNodeResult::Succeeded;
}

void UBTTaskNode_Attack::ComboActionBegin()
{
	// Combo Status
	CurrentCombo = 1;

	// Movement Setting
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	// Animation Setting
	const float AttackSpeedRate = 1.0f; 
	UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance(); 
	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);
	UE_LOG(LogTemp, Warning, TEXT("%s"), AnimInstance);

	// Montage End Delegate
	FOnMontageEnded EndDelegate; 
	EndDelegate.BindUObject(this, &UBTTaskNode_Attack::ComboActionEnd); 
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate(); SetComboCheckTimer();
}

void UBTTaskNode_Attack::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0); CurrentCombo = 0; 
	UE_LOG(LogTemp, Warning, TEXT("COMBOATTACKEnd"));
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UBTTaskNode_Attack::SetComboCheckTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("COMBOATTACKTimer"));
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));
	const float AttackSpeedRate = 1.0f; 
	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this,
			&UBTTaskNode_Attack::ComboCheck, ComboEffectiveTime, false);
	}

}

void UBTTaskNode_Attack::ComboCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("COMBOATTACKCheck"));

	ComboTimerHandle.Invalidate();
	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount); FName NextSection = *FString::Printf(TEXT("%s%d"),
			*ComboActionData->MontageSectionNamePrefix, CurrentCombo); 
		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage); 
		SetComboCheckTimer(); HasNextComboCommand = false;
	}

}
