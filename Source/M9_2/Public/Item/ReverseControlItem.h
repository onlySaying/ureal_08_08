// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "ReverseControlItem.generated.h"

UCLASS()
class M9_2_API AReverseControlItem : public ABaseItem
{
	GENERATED_BODY()
	
public:	
	AReverseControlItem();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Reverse")
	float Duration;

	virtual void ActivateItem(AActor* Activator) override;


};
