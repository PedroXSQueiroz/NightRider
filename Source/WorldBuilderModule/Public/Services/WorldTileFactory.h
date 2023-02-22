// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include <Dtos/WorldTileParams.h>

#include <Utils/Constants.h>

#include "WorldTileFactory.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class WORLDBUILDERMODULE_API UWorldTileFactory : public UObject
{
	GENERATED_BODY()

public:
	
	void Setup(UWorld* world);

	class AWorldTile* Build(
			int xIndex
		,	int yIndex
		,	int zIndex
		,	UWorld* world
		,	float DeltaTime
		,	FVector* offset
	);

	
	AWorldTile* UWorldTileFactory::Build(
			int xIndex
		,	int yIndex
		,	int zIndex
		,	UWorld* world
	);

	AWorldTile* SetupTile(class AWorldTile* currentTile, struct FWorldTileIndexes* indexes, UWorld* world);

	int GetSymetricIndexes(ESingleAxis axis, int index, bool project);

	TMap<ESingleAxis, int> GetSymetricIndexes(
							ESingleAxis firstAxis
						,	int firstIndex
						,	ESingleAxis secondAxis
						,	int secondIndex
						,	bool project);

	TMap<ESingleAxis, int> GetSymetricIndexes(
							ESingleAxis firstAxis
						,	int firstIndex
						,	ESingleAxis secondAxis
						,	int secondIndex
						,	ESingleAxis thirdAxis
						,	int thirdIndex
						,	bool project);
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWorldTileParams Params = FWorldTileParams();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWorldTilesObservableContainer> ObservableContainerType;

	FWorldTileParams GetParams();

	void RemoveTile(class AWorldTile* tile);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnWorldTileCreated, class AWorldTile* tile)
	FOnWorldTileCreated& OnWorldTileCreated()
	{
		return this->OnWorldTileCreatedEvent;
	}

private:

	UWorld* CurrentWorldReference;

	class IWorldTilesObservable* ObservableReference;

	class UWorldTilesObservableContainer* ObservableContainer;
	
	//class UWorldTileParams* Params;

	void UpdateIndexesTracking(struct FWorldTileIndexes* indexes, bool isInserting = true);
	
	void UpdateIndexesTracking(ESingleAxis axis, int index, bool isInserting = true);

	int GetRangeBetweenIndexes(int start, int end);

	int GetMedianBetweenIndex(int start, int end);

	TArray<int>* GetTracking(ESingleAxis axis);

	TArray<int>* XIndexesTracking;

	TArray<int>* YIndexesTracking;

	TArray<int>* ZIndexesTracking;
	
	class UWordTileRecycle* Recycle;
	
	TMap<struct FWorldTileIndexes*, AWorldTile*> Tiles;

	FOnWorldTileCreated OnWorldTileCreatedEvent = FOnWorldTileCreated();

	FVector CalcLocationByIndexes(FWorldTileParams params, struct FWorldTileIndexes* indexes, float DeltaTime);

};
