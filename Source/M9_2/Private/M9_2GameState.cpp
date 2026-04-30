#include "M9_2GameState.h"

#include "SpawnVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Monster/EnemyBase.h"

AM9_2GameState::AM9_2GameState()
{
    // 기본값 설정
    WaveDuration = 30.0f;
    CurrentWaveIndex = 0;
}

void AM9_2GameState::BeginPlay()
{
    Super::BeginPlay();

    // 맵에 배치된 SpawnVolume을 자동으로 찾아서 연결 (에디터에서 수동 할당 안 했을 경우 대비)
    if (!TargetSpawnVolume)
    {
        TargetSpawnVolume = Cast<ASpawnVolume>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnVolume::StaticClass()));
    }

    StartWave();
}

void AM9_2GameState::StartWave()
{
    // 1. 웨이브 인덱스 증가 및 남은 시간 초기화
    CurrentWaveIndex++;
    RemainingTime = WaveDuration;

    // 2. 스폰 위치 결정 (SpawnVolume 범위 활용)
    FVector FinalSpawnLocation = SpawnLocation; 

    if (TargetSpawnVolume)
    {
        // SpawnVolume에 구현된 랜덤 위치 계산 함수 호출
        FinalSpawnLocation = TargetSpawnVolume->GetRandomPointInVolume();
        // 슬라임이 바닥에 파묻히지 않도록 Z축 보정 (필요 시)
        FinalSpawnLocation.Z += 50.0f; 
    }

    // 3. 슬라임 소환
    if (EnemyClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        GetWorld()->SpawnActor<AEnemyBase>(
            EnemyClass, 
            FinalSpawnLocation, 
            FRotator::ZeroRotator, 
            SpawnParams
        );
    }

    // 4. 메시지 출력
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, 
            FString::Printf(TEXT("웨이브 %d 시작! 범위 내에서 슬라임이 나타났습니다!"), CurrentWaveIndex));
    }

    // 5. 타이머 작동 (1초마다 UpdateTimer 호출, WaveDuration 후 EndWave 호출)
    GetWorldTimerManager().SetTimer(TickTimerHandle, this, &AM9_2GameState::UpdateTimer, 1.0f, true);
    GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &AM9_2GameState::EndWave, WaveDuration, false);
}

void AM9_2GameState::UpdateTimer()
{
    RemainingTime -= 1.0f;

    // 화면에 남은 시간 카운트다운 표시
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, 1.1f, FColor::White, 
            FString::Printf(TEXT("다음 웨이브까지: %d초"), (int32)RemainingTime));
    }
}

void AM9_2GameState::EndWave()
{
    // 타이머 초기화
    GetWorldTimerManager().ClearTimer(TickTimerHandle);

    // 3웨이브까지는 다음 웨이브 시작, 그 이후는 맵 이동
    if (CurrentWaveIndex < 3)
    {
        StartWave();
    }
    else
    {
        // 모든 웨이브 종료 시 레벨 이동 로직 호출
        FString CurrentMapName = GetWorld()->GetMapName();
        CurrentMapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix); // 접두어(UEDPIE_0_ 등) 제거

        FString NextMapName;

        // 맵 이름에 따른 다음 레벨 결정
        if (CurrentMapName == TEXT("FirstPersonMap")) NextMapName = TEXT("FirstPersonMap1");
        else if (CurrentMapName == TEXT("FirstPersonMap1")) NextMapName = TEXT("FirstPersonMap2");
        else 
        {
            if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("축하합니다! 모든 레벨을 클리어했습니다!"));
            return;
        }

        // 다음 레벨로 이동
        UGameplayStatics::OpenLevel(GetWorld(), FName(*NextMapName));
    }
}