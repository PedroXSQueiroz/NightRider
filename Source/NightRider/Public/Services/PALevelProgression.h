// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/LevelProgression.h"
#include "PALevelProgression.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class NIGHTRIDER_API UPALevelProgression : public ULevelProgression
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LevelThresholdFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseLevelPoints;

	virtual float GetThresholdPointsOfLevel(int level) override;

};
