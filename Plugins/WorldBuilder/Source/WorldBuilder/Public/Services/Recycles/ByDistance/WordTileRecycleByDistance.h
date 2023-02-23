// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Services/WordTileRecycle.h>

#include <Utils/Constants.h>

#include "WordTileRecycleByDistance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class WORLDBUILDER_API UWordTileRecycleByDistance : public UWordTileRecycle
{
	GENERATED_BODY()

public:

	void Setup( class UWorldTileFactory* factory, class UWorld* world, class IWorldTilesObservable* reference) override;
	
	virtual bool ShouldRecycle(class AWorldTile* tile) override;

	virtual bool CanTileBeRecycled(class AWorldTile* tile) override;

	virtual struct FWorldTileIndexes* GetNextIndexes(class AWorldTile* tile) override;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float MaxDistanceToSpawn;

private:

	class UWorldTileFactory* CurrentTileFactory;

	class IWorldTilesObservable* Reference;

	EAxisAlignment Alignment;

	float GetCurrentDistanceFromRef(AWorldTile* tile);

	float Distance(float start, float end);

	float Distance(FVector2D start, FVector2D end);

	float Distance(FVector start, FVector end);
};
