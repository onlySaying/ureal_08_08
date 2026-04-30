// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(Scene);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Scene);
	
	// 이벤트 바인딩
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);

}

void ABaseItem::OnItemOverlap(
		UPrimitiveComponent* OverlapComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyComp,
		bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		ActivateItem(OtherActor);
	}
}

void ABaseItem::ActivateItem(AActor* Activator)
{
	if (PickupParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), 
			PickupParticle, 
			GetActorLocation(),
			GetActorRotation(),
			true
			);
	}
	
	if (PickupSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			GetWorld(),
			PickupSound,
			GetActorLocation(),
			GetActorRotation(),
			true
			);
	}
	
}

FName ABaseItem::GetItemType() const
{
	return ItemType;
}

void ABaseItem::OnItemEndOverlap(
		UPrimitiveComponent* OverlapComp, AActor* OhterActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyComp)
{
	
}

void ABaseItem::DestroyItem()
{
	Destroy();
}

