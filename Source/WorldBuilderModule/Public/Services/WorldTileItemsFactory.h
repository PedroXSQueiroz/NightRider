// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldTileItemsFactory.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class WORLDBUILDERMODULE_API UWorldTileItemsFactory : public UObject
{
	GENERATED_BODY()

public:

	virtual TArray<class UWorldTileItemData*> BuildItemForTile(class AWorldTile* tile) PURE_VIRTUAL( TEXT("NOT IMPLEMENTED YET"), return TArray<class UWorldTileItemData*>(); );
	
};
