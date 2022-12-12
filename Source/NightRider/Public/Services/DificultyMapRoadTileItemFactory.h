// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/RoadTileItemFactory.h"
#include "DificultyMapRoadTileItemFactory.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class NIGHTRIDER_API UDificultyMapRoadTileItemFactory : public URoadTileItemFactory
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<AActor>, float> ItemToDificulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDificultyByLavelFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinDificultyByLavelFactor;

	virtual TArray<TSubclassOf<AActor>> GetItems(class ARoadTileSection* target) override;

private:

	int FindFreeTrailItem(ARoadTileSection* tile);
};
