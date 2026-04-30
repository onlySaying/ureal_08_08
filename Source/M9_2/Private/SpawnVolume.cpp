#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

ASpawnVolume::ASpawnVolume()
{
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);
}

void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	// 시작 시 10개의 아이템을 테이블 확률에 맞춰 스폰
	for (int32 i = 0; i < 10; i++) { SpawningRandomItem(); }
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();
	return BoxOrigin + FVector(FMath::FRandRange(-BoxExtent.X, BoxExtent.X), FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y), FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z));
}

AActor* ASpawnVolume::SpawningRandomItem()
{
	if (FItemSpawnRow* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get()) return SpawnItem(ActualClass);
	}
	return nullptr;
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	if (!ItemDataTable) return nullptr;
	TArray<FItemSpawnRow*> AllRows;
	ItemDataTable->GetAllRows<FItemSpawnRow>(TEXT("Context"), AllRows);
    
	float TotalChance = 0.0f;
	for (auto Row : AllRows) TotalChance += Row->SpawnChance;

	float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0.0f;

	for (auto Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance) return Row;
	}
	return nullptr;
}

AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	return GetWorld()->SpawnActor<AActor>(ItemClass, GetRandomPointInVolume(), FRotator::ZeroRotator);
}