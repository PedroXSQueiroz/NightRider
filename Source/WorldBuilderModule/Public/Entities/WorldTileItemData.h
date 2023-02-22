// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldTileItemData.generated.h"

/**
 * 
 */
UCLASS()
class WORLDBUILDERMODULE_API UWorldTileItemData : public UObject
{
	GENERATED_BODY()

public:

	AActor* Item;

	FTransform RelativeTransform;

};
