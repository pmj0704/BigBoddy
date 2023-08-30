// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	struct Data  //������
	{
		int hp;
		int damage;
	};
public:
	 bool bUnstoppable; //�����Ұ�
	 bool bInvincible; // ����
public:

	UFUNCTION(BlueprintCallable, Category = BaseFuction)
	virtual void Move(); //�̵�

	UFUNCTION(BlueprintCallable, Category = BaseFuction)
	virtual void Attack(); //����

	UFUNCTION(BlueprintCallable, Category = BaseFuction)
	virtual void Damaged(); //������ �޾�����

	UFUNCTION(BlueprintCallable, Category = BaseFuction)
	virtual void ChangeHp(); //HP����
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
