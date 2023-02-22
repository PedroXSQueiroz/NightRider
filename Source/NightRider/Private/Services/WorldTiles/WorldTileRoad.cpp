// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/WorldTiles/WorldTileRoad.h"

int AWorldTileRoad::GetTrailsCount()
{
	return this->TrailsCount;
}

AWorldTileRoad* AWorldTileRoad::GetTileBefore()
{
	return nullptr;
}

FVector AWorldTileRoad::GetTrailMedianPosition(int index)
{
	
	float trailGap = this->SizeX / this->TrailsCount;
	float gapMedian = trailGap / 2;

	FVector roadLocation = this->GetActorLocation();

	float startOffset = roadLocation.Y - ((trailGap * this->TrailsCount) / 2);

	if (index <= 0)
	{
		return FVector(roadLocation.X, gapMedian + startOffset, roadLocation.Z);
	}

	if (index >= this->TrailsCount)
	{
		return FVector(roadLocation.X, ((trailGap * (this->TrailsCount - 1)) + gapMedian) + startOffset, roadLocation.Z);
	}

	float yMedianTrailPosition = ((index * trailGap) + gapMedian) + startOffset;

	return FVector(roadLocation.Y, yMedianTrailPosition, roadLocation.Z);

}
