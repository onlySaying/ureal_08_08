#include "M9HUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

// 생성자: 변수 초기화
AM9HUD::AM9HUD()
    : HUDWidgetClass(nullptr)
    , HUDWidgetInstance(nullptr)
    , MainMenuWidgetClass(nullptr)
    , MainMenuWidgetInstance(nullptr)
{
}

void AM9HUD::BeginPlay()
{
    Super::BeginPlay();

    // 현재 맵 이름을 가져와서 메뉴 레벨인지 확인
    FString CurrentMapName = GetWorld()->GetMapName();
    
    // 엔진에서 맵 이름 앞에 붙는 접두어(UEDPIE_ 등)를 고려하여 Contains 사용
    if (CurrentMapName.Contains(TEXT("MenuLevel")))
    {
        ShowMainMenu(false);
    }
    else
    {
        ShowGameHUD();
    }
}

void AM9HUD::ShowGameHUD()
{
    APlayerController* PC = GetOwningPlayerController();
    if (!PC) return;

    // 기존 위젯 제거 (중복 생성 방지)
    if (MainMenuWidgetInstance) 
    {
        MainMenuWidgetInstance->RemoveFromParent();
        MainMenuWidgetInstance = nullptr;
    }

    if (HUDWidgetClass)
    {
        HUDWidgetInstance = CreateWidget<UUserWidget>(PC, HUDWidgetClass);
        if (HUDWidgetInstance)
        {
            HUDWidgetInstance->AddToViewport();
            
            // 게임 플레이 모드로 설정
            PC->bShowMouseCursor = false;
            PC->SetInputMode(FInputModeGameOnly());
        }
    }
}

void AM9HUD::ShowMainMenu(bool bIsRestart)
{
    APlayerController* PC = GetOwningPlayerController();
    if (!PC) return;

    // 기존 위젯 제거
    if (HUDWidgetInstance)
    {
        HUDWidgetInstance->RemoveFromParent();
        HUDWidgetInstance = nullptr;
    }

    if (MainMenuWidgetClass)
    {
        MainMenuWidgetInstance = CreateWidget<UUserWidget>(PC, MainMenuWidgetClass);
        if (MainMenuWidgetInstance)
        {
            MainMenuWidgetInstance->AddToViewport();
            
            // UI 모드로 설정 및 마우스 커서 표시
            PC->bShowMouseCursor = true;
            FInputModeUIOnly InputMode;
            InputMode.SetWidgetToFocus(MainMenuWidgetInstance->TakeWidget());
            PC->SetInputMode(InputMode);

            // 위젯 내부의 텍스트나 애니메이션 제어 (이전 로직 활용)
            UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText")));
            if (ButtonText)
            {
                if (bIsRestart)
                {
                    ButtonText->SetText(FText::FromString(TEXT("Restart")));
                    
                    // 블루프린트에 선언된 GameOver 애니메이션 함수 호출 (있을 경우)
                    UFunction* AnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
                    if (AnimFunc)
                    {
                        MainMenuWidgetInstance->ProcessEvent(AnimFunc, nullptr);
                    }
                }
                else
                {
                    ButtonText->SetText(FText::FromString(TEXT("Start")));
                }
            }
        }
    }
}