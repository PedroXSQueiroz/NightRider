// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/Ranking.h"
#include "PARanking.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class NIGHTRIDER_API UPARanking : public URanking
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LevelFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RankingAFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RankingBFactor;

	virtual float GetARankingThreshold(int level) override;

	virtual float GetBRankingThreshold(int level) override;
};
