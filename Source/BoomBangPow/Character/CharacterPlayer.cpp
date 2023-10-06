// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerUI.h"
#include "Meng_SoundActor.h"
#include "Collision.h"
#include "EnemyComboAttackData.h"
#include "GameFramework/Actor.h" 
#include "Engine/DataAsset.h"

ACharacterPlayer::ACharacterPlayer()
{
	//Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(L"BBP_Capsule");
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));



	//Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Minyoung/Input/IMC_TPS.IMC_TPS'"));
	if (InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>JumpActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Minyoung/Input/IA_Jump.IA_Jump'"));
	if (JumpActionRef.Object)
	{
		JumpAction = JumpActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>MoveActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Minyoung/Input/IA_Move.IA_Move'"));
	if (MoveActionRef.Object)
	{
		MoveAction = MoveActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>LookActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Minyoung/Input/IA_Look.IA_Look'"));
	if (LookActionRef.Object)
	{
		LookAction = LookActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>AttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Minyoung/Input/AttackAction.AttackAction'"));
	if (AttackActionRef.Object)
	{
		AttackAction = AttackActionRef.Object;
	}
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* playerController = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	if (subSystem)
	{
		subSystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ACharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::Look);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::Attack);
}

void ACharacterPlayer::Move(const FInputActionValue& value)
{
	if (canAnim)
	{
		FVector2D MovementVector = value.Get<FVector2D>();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void ACharacterPlayer::Look(const FInputActionValue& value)
{
	if (canAnim)
	{
		FVector2D LookAxisVector = value.Get<FVector2D>();

		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACharacterPlayer::Attack()
{
	if (canAnim)
	{
		UE_LOG(LogTemp, Log, TEXT("Attack"));
		ProcessComboCommand();
	}
}

void ACharacterPlayer::AttackHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Parmas(SCENE_QUERY_STAT(Attack), false, this);


	const float AttackRange = 40.0f;
	const float AttackRadius = 50.0f;
	const float AttackDamage = 30.0f;
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();

	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(AttackRadius), Parmas);

	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
	}
#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 5.0f);


#endif // ENABLE_DRAW_DEBUG

}

float ACharacterPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	SetHit(DamageAmount);
	return DamageAmount;
}

void ACharacterPlayer::SetHit(float _Damage)
{
	hp -= _Damage;
	if (hp < 1)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		SetDead();
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		PlayHitAnimation();
	}
}

void ACharacterPlayer::ReturnWalking()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ACharacterPlayer::PlayHitAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(HurtMontage, 1.0f);
	// EndDelegate;
//	EndDelegate.BindUObject(this, &ACharacterPlayer::ReturnWalking);
	//AnimInstance->Montage_SetEndDelegate(EndDelegate, HurtMontage);
}

void ACharacterPlayer::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
}

void ACharacterPlayer::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	isDead = true;
	AnimInstance->Montage_Play(DieMontage, 1.0f);
}

void ACharacterPlayer::ProcessComboCommand()
{
	float attackDamage = soundScale * 100;

	UE_LOG(LogTemp, Log, TEXT("%f"), attackDamage);

	if (attackDamage >= 0.0f && attackDamage < 20.0f)
	{
		CurrentCombo = 1;
		Damage = 5;
	}
	else if (attackDamage >= 20.0f && attackDamage < 30.0f)
	{
		CurrentCombo = 2;
		Damage = 10;
	}
	else if (attackDamage >= 30.0f && attackDamage < 40.0f)
	{
		CurrentCombo = 3;
		Damage = 15;
	}
	else if (attackDamage >= 40.0f && attackDamage < 50.0f)
	{
		CurrentCombo = 4;
		Damage = 20;
	}
	else if (attackDamage >= 50.0f && attackDamage < 60.0f)
	{
		CurrentCombo = 5;
		Damage = 25;
	}
	else if (attackDamage >= 60.0f && attackDamage < 100.0f)
	{
		CurrentCombo = 6;
		Damage = 30;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Error"));
	}


	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	FName NextSection = *FString::Printf(TEXT("%s%d"),
		*ComboActionData->MontageSectionNamePrefix, CurrentCombo);
	UE_LOG(LogTemp, Log, TEXT("%s%d"),
		*ComboActionData->MontageSectionNamePrefix, CurrentCombo);

	const float AttackSpeedRate = 1.0f;
	canAnim = false;
	AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	//if (!ComboTimerHandle.IsValid())
	//{
	//	HasNextComboCommand = false;
	//}
	//else
	//{
	//	HasNextComboCommand = true;
	//}


	UE_LOG(LogTemp, Log, TEXT("AttackAs: %d"), CurrentCombo);
	//ComboActionBegin();
}

void ACharacterPlayer::ComboActionBegin()
{
	// Animation Setting
	UE_LOG(LogTemp, Log, TEXT("ComboActionBegin"), CurrentCombo);

	const float AttackSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);
	// Montage End Delegate
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ACharacterPlayer::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void ACharacterPlayer::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	UE_LOG(LogTemp, Log, TEXT("ComboActionEnd"), CurrentCombo);
	//GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ACharacterPlayer::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));
	const float AttackSpeedRate = 1.0f;
	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] /
		ComboActionData->FrameRate) / AttackSpeedRate;
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this,
			&ACharacterPlayer::ComboCheck, ComboEffectiveTime, false);
	}
}
void ACharacterPlayer::ComboCheck()
{
	UE_LOG(LogTemp, Log, TEXT("ComboCheck"));
	ComboTimerHandle.Invalidate();
	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		FName NextSection = *FString::Printf(TEXT("%s%d"),
			*ComboActionData->MontageSectionNamePrefix, CurrentCombo);
		UE_LOG(LogTemp, Log, TEXT("%s%d"),
			*ComboActionData->MontageSectionNamePrefix, CurrentCombo);

		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
		SetComboCheckTimer();
		HasNextComboCommand = false;
	}
}
