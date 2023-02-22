// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/WorldTileMeshFactory.h"
#include "MeshFactoryRoad.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class NIGHTRIDER_API UMeshFactoryRoad : public UWorldTileMeshFactory
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere, BlueprintReadWrite)
	FVector GroundRoadPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* GroundRoadMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("ROAD_MESH"));

	virtual TArray<class UWorldTileMeshData*> BuildMeshForTile(class AWorldTile* tile) override;
	
};
