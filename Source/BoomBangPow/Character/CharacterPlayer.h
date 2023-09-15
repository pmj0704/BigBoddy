// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "InputActionValue.h"
#include "CharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BOOMBANGPOW_API ACharacterPlayer : public ACharacterBase
{









	GENERATED_BODY()

public:
	ACharacterPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UCameraComponent> FollowCamera;


	//Input Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> LookAction;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
};
