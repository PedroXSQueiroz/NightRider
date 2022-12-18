// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/MultiplierOnDistance.h"

AMultiplierOnDistance::AMultiplierOnDistance()
{
	PrimaryActorTick.bCanEverTick = true;
}

float AMultiplierOnDistance::GetValue()
{
	return 2;
}

void AMultiplierOnDistance::BeginPlay()
{
	Super::BeginPlay();
}

void AMultiplierOnDistance::Tick(float deltatime)
{
	Super::Tick(deltatime);
}
