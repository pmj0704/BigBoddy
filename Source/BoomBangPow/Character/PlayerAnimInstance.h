// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BOOMBANGPOW_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPlayerAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSecondes) override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		TObjectPtr<class UCharacterMovementComponent> Movement;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		float MovingThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		uint8 bIsJumping : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		float JumpingThreshold;
};
