// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldTileMeshFactory.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class WORLDBUILDERMODULE_API UWorldTileMeshFactory : public UObject
{
	GENERATED_BODY()

public:

	virtual TArray<class UWorldTileMeshData*> BuildMeshForTile(class AWorldTile* tile) PURE_VIRTUAL( TEXT("NOT IMPLEMENTED YET"), return TArray<UWorldTileMeshData*>(););
	
};
