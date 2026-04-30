// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SlowingItem.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "M9_2/M9_2Character.h"

// Sets default values
ASlowingItem::ASlowingItem()
{
 	PrimaryActorTick.bCanEverTick = false;

	ItemType = "SlowingItem";
	SlowAmount = 0.5f;
	Duration = 5.0f;
}

void ASlowingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (AM9_2Character* Player = Cast<AM9_2Character>(Activator))
	{
		if (UCharacterMovementComponent* MoveComp = Player->GetCharacterMovement())
		{
			float OriginalSpeed = MoveComp->MaxWalkSpeed;
			MoveComp->MaxWalkSpeed *= 0.5f; // 50% 속도 감소

			FTimerHandle SlowTimerHandle;
			// 5초 뒤 속도 복구 (람다 함수 사용)
			GetWorld()->GetTimerManager().SetTimer(SlowTimerHandle, [MoveComp, OriginalSpeed]()
			{
				if (MoveComp)
				{
					MoveComp->MaxWalkSpeed = OriginalSpeed;
				}
			}, 5.0f, false);
		}
	}
	DestroyItem();
}

