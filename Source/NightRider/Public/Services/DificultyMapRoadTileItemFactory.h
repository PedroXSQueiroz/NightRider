// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/RoadTileItemFactory.h"
#include "DificultyMapRoadTileItemFactory.generated.h"

USTRUCT(BlueprintType)
struct FPossibilityRange 
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Max;

};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class NIGHTRIDER_API UDificultyMapRoadTileItemFactory : public URoadTileItemFactory
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<AActor>, FPossibilityRange> ItemToDificulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDificultyByLavelFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinDificultyByLavelFactor;

	virtual TArray<TSubclassOf<AActor>> GetItems(class ARoadTileSection* target) override;

private:

	int FindFreeTrailItem(ARoadTileSection* tile);
};
