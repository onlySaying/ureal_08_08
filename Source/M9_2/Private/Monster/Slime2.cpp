// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Slime2.h"
#include "GameFramework/CharacterMovementComponent.h"

ASlime2::ASlime2()
{
	DamageAmount = 20.0f;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f; // 일반 속도
}
