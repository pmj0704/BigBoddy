// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "C:\Program Files\Epic Games\UE_5.1\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\EnhancedInputComponent.h"

void APlayerCharacter::Move()
{

}

void APlayerCharacter::Attack()
{
}

void APlayerCharacter::Damaged()
{
}

void APlayerCharacter::ChangeHp()
{
}

void APlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	float Movement = Value.Get<float>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDir, Movement);
	}
}

void APlayerCharacter::MoveRight(const FInputActionValue& Value)
{
	float Movement = Value.Get<float>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightDir, Movement);
	}
}
