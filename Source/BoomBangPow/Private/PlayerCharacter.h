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
	UFUNCTION(BlueprintCallable, Category = BaseFuction)
	virtual void Move() override;

	UFUNCTION(BlueprintCallable, Category = BaseFuction)
	virtual void Attack() override;

	UFUNCTION(BlueprintCallable, Category = BaseFuction)
	virtual void Damaged() override;

	UFUNCTION(BlueprintCallable, Category = BaseFuction)
	virtual void ChangeHp() override;

#pragma region 이동 회전 함수
	void MoveForawrd(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
#pragma endregion



#pragma region Input


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* tpsMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* moveForawrdAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* moveRightAction;
#pragma endregion
};
