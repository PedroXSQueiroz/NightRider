// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Ranking.generated.h"

UENUM()
enum ERanking
{
	A,
	B,
	C
};


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NIGHTRIDER_API URanking : public UObject
{
	GENERATED_BODY()
	
public:

	virtual float GetARankingThreshold(int level) PURE_VIRTUAL(TEXT("NOT IMPLEMENTED YET"), return -1;);

	virtual float GetBRankingThreshold(int level) PURE_VIRTUAL(TEXT("NOT IMPLEMENTED YET"), return -1;);

};
