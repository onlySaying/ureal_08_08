// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "M9HUD.generated.h"

/**
 * 
 */
UCLASS()
class M9_2_API AM9HUD : public AHUD
{
	GENERATED_BODY()
public:
	
	AM9HUD();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;
    
	UPROPERTY(BlueprintReadWrite, Category = "HUD")
	UUserWidget* HUDWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
    
	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	UUserWidget* MainMenuWidgetInstance;
	
	void ShowGameHUD();
	void ShowMainMenu(bool bIsRestart = false);

protected:
	virtual void BeginPlay() override;
};
