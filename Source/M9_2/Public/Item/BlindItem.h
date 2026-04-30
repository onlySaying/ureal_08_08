// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "BlindItem.generated.h"

UCLASS()
class M9_2_API ABlindItem : public ABaseItem
{
	GENERATED_BODY()
	
public:	
	ABlindItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Blind")
	float Duration;

	virtual void ActivateItem(AActor* Activator) override;

};
