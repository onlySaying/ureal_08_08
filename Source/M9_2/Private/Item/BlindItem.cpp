#include "Item/BlindItem.h"
#include "Blueprint/UserWidget.h" // UI 사용 시 필요
#include "GameFramework/Character.h"
#include "M9_2/M9_2Character.h"

ABlindItem::ABlindItem()
{
	ItemType = "BlindItem";
	Duration = 3.0f;
}

void ABlindItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (AM9_2Character* Player = Cast<AM9_2Character>(Activator))
	{
		if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
		{
			// 마우스 회전(Look 입력)을 3초간 무시합니다.
			PC->SetIgnoreLookInput(true);

			FTimerHandle BlindTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(BlindTimerHandle, [PC]()
			{
				if (PC)
				{
					PC->SetIgnoreLookInput(false);
				}
			}, 3.0f, false);
		}
	}
	DestroyItem();
}