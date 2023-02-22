// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include <Utils/Constants.h>

#include "WorldTileParams.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FWorldTileParams
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SizeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SizeZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxTilesX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxTilesY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxTilesZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWorldTileMeshFactory> MeshFactoryType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWorldTileItemsFactory> ItemsFactoryType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWordTileRecycle> RecycleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAxisAlignment AxisAlignment;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AWorldTile> WorldTileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RelativeMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SpawnNewTileOnlyOnBorders = true;

	static FWorldTileParams Copy(FWorldTileParams* params);


};
