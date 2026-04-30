#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"

class USphereComponent;

UCLASS()
class M9_2_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName ItemType;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USphereComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Effects")
	UParticleSystem* PickupParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Effects")
	USoundBase* PickupSound;
	
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
	
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemType() const override;
	
	virtual void DestroyItem();
};
