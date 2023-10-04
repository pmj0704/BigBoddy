// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "BaseCharacter.h"
//#include"Perception/AIPerceptionTypes.h"
#include "GameFramework/Character.h"
#include "Interface/AnimationAttackInterface.h"
#include "EnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Stun,
	Combat,
	Dead
};

UCLASS()
class AEnemyCharacter : public ACharacter, public IAnimationAttackInterface
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
		TObjectPtr<class UAnimMontage> HurtMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		TObjectPtr<class UAnimMontage> DieMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, Meta = (AllowPrivateAccess = "true"))
		int hp = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, Meta = (AllowPrivateAccess = "true"))
		int damage = 20.0f;

	void DestroyActor();

public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void AttackHitCheck();
};
