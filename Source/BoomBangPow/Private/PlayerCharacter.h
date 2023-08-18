// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "C:\Program Files\Epic Games\UE_5.1\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\InputActionValue.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
		
public: 
	virtual void Move() override;

	virtual void Attack() override;

	virtual void Damaged() override;

	virtual void ChangeHp() override;

	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);




public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* tpsMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* moveForawrdAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* moveRightAction;
};
