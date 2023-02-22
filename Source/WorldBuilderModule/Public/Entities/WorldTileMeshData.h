// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"



#include "WorldTileMeshData.generated.h"

/**
 * 
 */
UCLASS()
class WORLDBUILDERMODULE_API UWorldTileMeshData : public UObject
{
	GENERATED_BODY()

public:

	UStaticMesh* Mesh;

	FTransform RelativeFransform;
	
};
