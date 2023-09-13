// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Meng_SoundActor.generated.h"

UCLASS()
class AMeng_SoundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeng_SoundActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound)
		USoundBase* sound;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound)
	//	Synes 

	float duration;
	float playedTime;
};
