// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/RelativeVelocityObserverComponent.h"

#include <Services/WorldBuilder.h>

// Sets default values
URelativeVelocityObserverComponent::URelativeVelocityObserverComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void URelativeVelocityObserverComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void URelativeVelocityObserverComponent::OnUpdateDistanceToRferenceUpdate(float newDistance, float distanceDealocated, float atTime) 
{
	if( this->IsBorder && newDistance > this->MaxDistanceFromRefeence ) 
	{
		this->WorldBuilderOrigin->CycleForward(distanceDealocated);
	}
}

// Called every frame
void URelativeVelocityObserverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void URelativeVelocityObserverComponent::SetMaxDistanceFromReference(float distance) 
{
	this->MaxDistanceFromRefeence = distance;
}

void URelativeVelocityObserverComponent::SetIsBorder(bool isBorder) 
{
	this->IsBorder = isBorder;
}

void URelativeVelocityObserverComponent::SetWorldBuilderOrigin(UWorldBuilder* origin)
{
	this->WorldBuilderOrigin = origin;
}
