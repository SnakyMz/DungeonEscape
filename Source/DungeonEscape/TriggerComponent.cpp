// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MoverActor)
	{
		MoverComponent = MoverActor->FindComponentByClass<UMover>();
	}

	OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator") && MoverComponent && !bIsTriggered)
	{
		ActorCount++;
		Trigger(true);
	}
}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator") && MoverComponent)
	{
		ActorCount--;
		if (ActorCount == 0 && bIsTriggered)
		{
			Trigger(false);
		}
	}
}

void UTriggerComponent::Trigger(bool NewTrigger)
{
	bIsTriggered = NewTrigger;
	if (MoverComponent && bCanTrigger)
	{
		MoverComponent->bOpen = NewTrigger;
	}
}