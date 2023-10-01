// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyComboAttackData.generated.h"

/**
 * 
 */
UCLASS()
class BOOMBANGPOW_API UEnemyComboAttackData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UEnemyComboAttackData();
public:
	UPROPERTY(EditAnywhere, Category = Name)
		FString MontageSectionNamePrefix;
	UPROPERTY(EditAnywhere, Category = Name)
		uint8 MaxComboCount;
	UPROPERTY(EditAnywhere, Category = Name)
		float FrameRate;
	UPROPERTY(EditAnywhere, Category = Name)
		TArray<float> EffectiveFrameCount;

};
