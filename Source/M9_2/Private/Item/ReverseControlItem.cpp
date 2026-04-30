#include "Item/ReverseControlItem.h"
#include "GameFramework/Character.h"
#include "M9_2/M9_2Character.h"

AReverseControlItem::AReverseControlItem()
{
	ItemType = "ReverseControlItem";
	Duration = 5.0f;
}

void AReverseControlItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (AM9_2Character* Player = Cast<AM9_2Character>(Activator))
	{
		// 캐릭터의 Move 함수에서 입력을 반전시키도록 명령 (5초간)
		Player->ApplyControlReverse(5.0f);
	}
	DestroyItem();
}