#pragma once

#include "EnemyCharacter.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/Character.h"
#include "EnemyAI.generated.h"

UCLASS()
class AEnemyAI : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAI();
	virtual void OnPossess(APawn* InPawn) override;
	
	static const FName Key_DefaultPos;
	static const FName Key_PatrolPos;
	static const FName Key_PlayerActor;
	static const FName Key_PlayerActorPos;
	static const FName Key_StateMode;

	void RunAI();
	void StopAI();

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;

	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void CheckSightPlayer(AActor* SightActor);

	UFUNCTION(BlueprintCallable, Category = "State")
	EEnemyState GetEnemyState();

	UFUNCTION()
	void SetEnemyState(EEnemyState setState);

public:

	UPROPERTY()
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(Category = Speed, EditAnywhere)
	float SightDistance = 1500.0f;

	AEnemyCharacter* OwnerPawn;
};
