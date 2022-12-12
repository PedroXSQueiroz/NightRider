// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelProgression.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class NIGHTRIDER_API ULevelProgression : public UObject
{
	GENERATED_BODY()

public:

	virtual float GetThresholdPointsOfLevel(int level) PURE_VIRTUAL(TEXT("NOT IMPLEMENTED YET"), return -1;);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class URanking> RankingService;
	
	enum ERanking GetRanking(int level, float points);

};
