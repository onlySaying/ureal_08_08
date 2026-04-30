// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealingItem.generated.h"

UCLASS()
class M9_2_API AHealingItem : public ABaseItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealingItem();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int32 HealAmount;
	
	virtual void ActivateItem(AActor* Activator) override;

};
