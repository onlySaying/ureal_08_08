#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "M9_2GameState.generated.h"

UCLASS()
class M9_2_API AM9_2GameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    AM9_2GameState();
    virtual void BeginPlay() override;

    // 설정값
    UPROPERTY(EditAnywhere, Category = "Wave") float WaveDuration = 30.0f; // 웨이브당 시간
    UPROPERTY(EditAnywhere, Category = "Wave") TSubclassOf<class AEnemyBase> EnemyClass; // 소환할 슬라임
    UPROPERTY(EditAnywhere, Category = "Wave") FVector SpawnLocation = FVector(0, 0, 100);

    // 상태값
    int32 CurrentWaveIndex = 0;
    float RemainingTime;

    void StartWave();
    void EndWave();
    void UpdateTimer();

    FTimerHandle WaveTimerHandle;
    FTimerHandle TickTimerHandle;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
    class ASpawnVolume* TargetSpawnVolume;
};