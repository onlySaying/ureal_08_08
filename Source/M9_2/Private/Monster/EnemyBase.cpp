#include "Monster/EnemyBase.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "M9_2/M9_2Character.h"
#include "Components/CapsuleComponent.h" // GetCapsuleComponent를 위해 반드시 필요!
#include "GameFramework/CharacterMovementComponent.h" // 슬라임 속도 조절 등을 위해 권장

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
    
	// 캡슐 컴포넌트 이벤트 바인딩
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlapBegin);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToPlayer();
}

void AEnemyBase::MoveToPlayer()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn) return;

	float Distance = FVector::Dist(GetActorLocation(), PlayerPawn->GetActorLocation());

	// 감지 범위 안에 플레이어가 있으면 추적 시작
	if (Distance <= DetectionRange)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController)
		{
			AIController->MoveToActor(PlayerPawn, 50.0f); // 50cm 거리까지 접근
		}
	}
}

void AEnemyBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 플레이어 캐릭터와 충돌했는지 확인
	AM9_2Character* Player = Cast<AM9_2Character>(OtherActor);
	if (Player)
	{
		// 이전에 작성했던 캐릭터의 TakeDamage 함수 호출
		Player->TakeDamage(DamageAmount);
        
		// 데미지 후 넉백 효과나 이펙트를 추가할 수 있습니다.
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("슬라임 공격! HP 감소"));
	}
}