#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class M9_2_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// 설정값
	UPROPERTY(EditAnywhere, Category = "Enemy Stats")
	float DetectionRange = 1000.0f; // 캐릭터를 발견하는 거리

	UPROPERTY(EditAnywhere, Category = "Enemy Stats")
	float DamageAmount = 10.0f;    // 캐릭터에게 주는 데미지

	// 추적 로직 함수
	void MoveToPlayer();

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
};