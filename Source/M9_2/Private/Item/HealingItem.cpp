// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HealingItem.h"

#include "M9_2/m9_2Character.h"

// Sets default values
AHealingItem::AHealingItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	HealAmount = 20; 
}
void AHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (ACharacter* PlayerCharacter = Cast<AM9_2Character>(Activator))
		{
			//PlayerCharacter->AddHealth(HealAmount);		
		}
		
	}
	this->DestroyItem();
}
