// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SlowingItem.generated.h"

UCLASS()
class M9_2_API ASlowingItem : public ABaseItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlowingItem();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Slowing")
	float SlowAmount; // 0.5f면 50% 감소

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Slowing")
	float Duration;

	virtual void ActivateItem(AActor* Activator) override;
};
