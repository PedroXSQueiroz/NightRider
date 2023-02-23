// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Entities/WorldTilesObservable.h>

#include "WorldTilesObservableContainer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class WORLDBUILDER_API UWorldTilesObservableContainer : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	virtual TScriptInterface<IWorldTilesObservable> GetReference(UWorld* world) PURE_VIRTUAL(TEXT("NOT IMPLEMENTED YET"), return nullptr; );

};
