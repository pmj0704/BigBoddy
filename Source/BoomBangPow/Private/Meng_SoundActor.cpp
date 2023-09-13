// Fill out your copyright notice in the Description page of Project Settings.


#include "Meng_SoundActor.h"

// Sets default values
AMeng_SoundActor::AMeng_SoundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMeng_SoundActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeng_SoundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

