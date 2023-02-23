// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "WordTileRecycle.generated.h"



/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class WORLDBUILDER_API UWordTileRecycle : public UObject
{
	GENERATED_BODY()

public:

	virtual void Setup(class UWorldTileFactory* factory, class UWorld* world, class IWorldTilesObservable* reference) PURE_VIRTUAL(TEXT("NOT IMPLEMENTED YET") );

	virtual bool ShouldRecycle(class AWorldTile* tile) PURE_VIRTUAL( TEXT("NOT IMPLEMENTED YET"), return false; );

	virtual bool CanTileBeRecycled(class AWorldTile* tile) PURE_VIRTUAL(TEXT("NOT IMPLEMENTED YET"), return false; );

	virtual struct FWorldTileIndexes* GetNextIndexes(class AWorldTile* tile) PURE_VIRTUAL(TEXT("NOT IMPLEMENTED YET"), return NULL; );

};
