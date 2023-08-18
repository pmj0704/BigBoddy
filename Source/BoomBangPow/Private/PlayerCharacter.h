// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
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

};
