// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/WorldTileItemsFactory.h"
#include "ItemFactoryRoad.generated.h"


class AWorldTile;


USTRUCT(BlueprintType)
struct FItemSpawnPossibilityRange
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
class NIGHTRIDER_API UItemFactoryRoad : public UWorldTileItemsFactory
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<AActor>, FItemSpawnPossibilityRange> ItemToDificulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDificultyByLavelFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinDificultyByLavelFactor;

	virtual TArray<class UWorldTileItemData*> BuildItemForTile(AWorldTile* tile) override;

private:

	int FindFreeTrailItem(AWorldTile* tile);
	
};
