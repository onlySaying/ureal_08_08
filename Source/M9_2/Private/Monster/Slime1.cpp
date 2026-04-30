// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Slime1.h"
#include "GameFramework/CharacterMovementComponent.h"

ASlime1::ASlime1()
{
	DamageAmount = 10.0f;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f; // 일반 속도
}
