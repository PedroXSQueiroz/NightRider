// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/WorldTilesObservableContainer.h"
#include "ObservableContainerCurrentPlayer.generated.h"

/**
 * 
 */
UCLASS()
class WORLDBUILDER_API UObservableContainerCurrentPlayer : public UWorldTilesObservableContainer
{
	GENERATED_BODY()

public:
	virtual TScriptInterface<IWorldTilesObservable> GetReference(UWorld* world) override;
	
};
