 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RoadTileItemFactory.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class NIGHTRIDER_API URoadTileItemFactory : public UObject
{
	GENERATED_BODY()
	
public:

	virtual TArray<TSubclassOf<AActor>> GetItems(class ARoadTileSection* target) PURE_VIRTUAL( TEXT("NOT IMPLREMENTED YET"), return TArray<TSubclassOf<AActor>>(); )
};
