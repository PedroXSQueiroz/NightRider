// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/WorldTile.h"
#include "WorldTileRoad.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTRIDER_API AWorldTileRoad : public AWorldTile
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	int TrailsCount;

	int GetTrailsCount();

	AWorldTileRoad* GetTileBefore();

	FVector GetTrailMedianPosition(int index);

private:



};
