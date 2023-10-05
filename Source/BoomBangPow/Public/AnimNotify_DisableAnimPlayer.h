// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Character/CharacterPlayer.h"
#include "AnimNotify_DisableAnimPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BOOMBANGPOW_API UAnimNotify_DisableAnimPlayer : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
