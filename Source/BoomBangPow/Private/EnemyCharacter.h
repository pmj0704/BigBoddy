#pragma once

#include "CoreMinimal.h"
//#include"Perception/AIPerceptionTypes.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

// 사용할 상태 정의
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UEnemyComboAttackData> ComboActionData;

};