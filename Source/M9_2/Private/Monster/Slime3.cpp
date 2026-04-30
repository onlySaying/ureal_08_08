// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Slime3.h"

#include "GameFramework/CharacterMovementComponent.h"

ASlime3::ASlime3()
{
	DamageAmount = 30.0f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f; // 일반 속도
}