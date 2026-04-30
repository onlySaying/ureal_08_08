// Copyright Epic Games, Inc. All Rights Reserved.

#include "M9_2PickUpComponent.h"

UM9_2PickUpComponent::UM9_2PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UM9_2PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UM9_2PickUpComponent::OnSphereBeginOverlap);
}

void UM9_2PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AM9_2Character* Character = Cast<AM9_2Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
