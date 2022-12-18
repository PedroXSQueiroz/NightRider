// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/Multiplier.h"
#include "MultiplierOnDistance.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTRIDER_API AMultiplierOnDistance : public AMultiplier
{
	GENERATED_BODY()

public:

	AMultiplierOnDistance();

	virtual void Tick(float deltatime) override;

	virtual float GetValue() override;

protected:

	virtual void BeginPlay() override;

private:

	float Value;

};
