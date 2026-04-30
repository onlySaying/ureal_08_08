// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class M9_2_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentLevelIndex; // 1, 2, 3 레벨 추적
};