#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/ItemSpawnRow.h" // 데이터 테이블 구조체 헤더
#include "SpawnVolume.generated.h"

UCLASS()
class M9_2_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ASpawnVolume();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Spawning") 
	class USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, Category = "Spawning") 
	class UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere, Category = "Spawning") 
	class UDataTable* ItemDataTable;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	FVector GetRandomPointInVolume() const;
	AActor* SpawningRandomItem();
	FItemSpawnRow* GetRandomItem() const;
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
	
};