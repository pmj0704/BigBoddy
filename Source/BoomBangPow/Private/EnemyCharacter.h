// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "BaseCharacter.h"
//#include"Perception/AIPerceptionTypes.h"
#include "GameFramework/Character.h"

#include "EnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Stun,
	Combat
};

UCLASS()
class AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
	AEnemyCharacter();

	virtual void Tick(float DeltaTime) override;

	ACharacter* ControlledCharacter;
	UCharacterMovementComponent* CharacterMovement;

	void ChangeSpeed(float speed);

	public:
	UPROPERTY(Category = State, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0"))
		EEnemyState mState = EEnemyState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		TObjectPtr<class UAnimMontage> HurtMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		TObjectPtr<class UAnimMontage> DieMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UEnemyComboAttackData> ComboActionData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, Meta = (AllowPrivateAccess = "true"))
		float hp = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, Meta = (AllowPrivateAccess = "true"))
		float damage = 20;

	UFUNCTION()
		void hitEnemy();

	void DestroyActor();
};
