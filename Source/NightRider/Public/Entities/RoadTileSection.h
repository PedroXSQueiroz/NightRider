// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/TileSection.h"
#include "RoadTileSection.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTRIDER_API ARoadTileSection : public ATileSection
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TrailsCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray< TSubclassOf<class AZombie> > DifcultiesToZombies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray< TSubclassOf<class AObstacle> > DifcultiesToObstacles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf< class URoadTileItemFactory > ItemFactoryType;

	class URoadTileItemFactory* ItemFactory;

	virtual void BeginPlay() override;

	bool IsInArea(FVector checkPosition);

	int GetTrailIndexIsIn(FVector checkPosition);

	FVector GetTrailMedianPosition(int index);

	virtual void Init(int dificulty, int dificultyMargin) override;

	void SetTileBefore(ARoadTileSection* before);

	ARoadTileSection* GetTileBefore();

	int GetTrailsCount();

	TArray<AActor*> GetItems();

protected:

	TArray<float> TrailRelativePositions;

	void BuildTrails(int riderTrailIndex);

	float TrailGap;

	int ObstaclesCount = 0;

	int ZombiesCount = 0;

	ARoadTileSection* Before;
};
