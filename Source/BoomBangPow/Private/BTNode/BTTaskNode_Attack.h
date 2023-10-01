// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyComboAttackData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BTTaskNode_Attack.generated.h"

/**
 * 
 */
UCLASS()
class UBTTaskNode_Attack : public UBTTaskNode
{
	GENERATED_BODY()

		UBTTaskNode_Attack();
	
		// Combo Action Section
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	void SetComboCheckTimer();
	void ComboCheck();

	ACharacter* OwnerCharacter;

	TObjectPtr<class UAnimMontage> ComboActionMontage;
	TObjectPtr<class UEnemyComboAttackData> ComboActionData;

};
