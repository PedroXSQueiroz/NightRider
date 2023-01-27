// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Record.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct NIGHTRIDER_API FRecord
{
	
	GENERATED_BODY()


public:

	FRecord();
	FRecord(
			float distanceRunned
		,	float totalZombiesKilled
		,	float totalPoints
		);
	
	UPROPERTY()
	float DistanceRunnned;

	UPROPERTY()
	int TotalZombiesKilled;

	UPROPERTY()
	float TotalPoints;

};
