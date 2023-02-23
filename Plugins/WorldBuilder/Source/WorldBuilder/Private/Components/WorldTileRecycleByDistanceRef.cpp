// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WorldTileRecycleByDistanceRef.h"

// Sets default values for this component's properties
UWorldTileRecycleByDistanceRef::UWorldTileRecycleByDistanceRef()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

FVector UWorldTileRecycleByDistanceRef::GetCurrentReferencePosition()
{
	return this->GetOwner()->GetActorLocation();
}


// Called when the game starts
void UWorldTileRecycleByDistanceRef::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWorldTileRecycleByDistanceRef::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
