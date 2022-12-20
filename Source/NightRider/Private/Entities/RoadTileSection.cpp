// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/RoadTileSection.h"

#include <Entities/Zombie.h>
#include <Entities/Obstacle.h>
#include <Services/WorldBuilder.h>
#include <Services/RoadTileItemFactory.h>

#include "UObject/Class.h"
#include <Entities/Rider.h>

void ARoadTileSection::BeginPlay() 
{
	Super::BeginPlay();

	this->TrailGap = this->SizeY / this->TrailsCount;
}

bool ARoadTileSection::IsInArea(FVector checkPosition)
{
	FVector roadTileLocation = this->GetActorLocation();

	float currentRoadTileXMedian = this->SizeX / 2;
	float currentRoadTileYMedian = this->SizeY / 2;

	float currentRoadTileInitialX = roadTileLocation.X - currentRoadTileXMedian;
	float currentRoadTileInitialY = roadTileLocation.Y - currentRoadTileXMedian;
	float currentRoadTileFinalX = roadTileLocation.X + currentRoadTileXMedian;
	float currentRoadTileFinalY = roadTileLocation.Y + currentRoadTileXMedian;

	return	currentRoadTileInitialX < checkPosition.X && checkPosition.X < currentRoadTileFinalX
		&&	currentRoadTileInitialY < checkPosition.Y && checkPosition.Y < currentRoadTileFinalY;
}

int ARoadTileSection::GetTrailIndexIsIn(FVector checkPosition)
{
	FVector roadLocation = this->GetActorLocation();

	float startOffset = roadLocation.Y - ((this->TrailGap * this->TrailsCount) / 2);
	
	for (int currentTrailIndex = 0; currentTrailIndex < this->TrailsCount; currentTrailIndex++) 
	{
		float startTrailGap = ( currentTrailIndex * this->TrailGap ) + startOffset;
		float endTrailGap	= ( ( currentTrailIndex + 1 )  * this->TrailGap ) + startOffset;

		bool isInTrailGap = startTrailGap < checkPosition.Y && checkPosition.Y < endTrailGap;

		if (isInTrailGap) 
		{
			return currentTrailIndex;
		}
	}
	
	return -1;
}

FVector ARoadTileSection::GetTrailMedianPosition(int index)
{
	float gapMedian = this->TrailGap / 2;
	
	FVector roadLocation = this->GetActorLocation();

	float startOffset = roadLocation.Y - ((this->TrailGap * this->TrailsCount) / 2);
	
	if (index <= 0) 
	{
		return FVector(roadLocation.X, gapMedian + startOffset, roadLocation.Z);
	}

	if (index >= this->TrailsCount) 
	{
		return FVector(roadLocation.X, ( ( this->TrailGap * ( this->TrailsCount - 1 ) ) + gapMedian) + startOffset, roadLocation.Z);
	}

	float yMedianTrailPosition = ((index * this->TrailGap) + gapMedian) + startOffset;

	return FVector(roadLocation.Y, yMedianTrailPosition, roadLocation.Z);
}

void ARoadTileSection::BuildTrails( int riderTrailIndex )
{
	float trailGapMedian	= this->TrailGap / 2;
	float trailPosition		= ( (this->SizeY / 2) * -1 ) + trailGapMedian;

	FVector currentRoadLocation = this->GetActorLocation();

	if (!this->ItemFactory) 
	{
		this->ItemFactory = this->ItemFactoryType.GetDefaultObject();
	}
	
	TArray<TSubclassOf<AActor>> itemTypes = this->ItemFactory->GetItems(this);

	for (int trailIndex = 0; trailIndex < this->TrailsCount; trailIndex++) 
	{
		trailPosition += trailIndex == 0 ? 0 : this->TrailGap;
		this->TrailRelativePositions.Add(trailPosition);

		TSubclassOf<AActor> itemType = itemTypes[trailIndex];

		if (itemType) 
		{
			AActor* currentItem = this->GetWorld()->SpawnActor<AActor>(
																itemType
															,	FTransform(
																	FVector(
																		currentRoadLocation.X,
																		trailPosition,
																		currentRoadLocation.Z
																	)
																)
															);
			currentItem->AttachToActor(
							this
						,	FAttachmentTransformRules(
								EAttachmentRule::KeepWorld
							,	EAttachmentRule::KeepRelative
							,	EAttachmentRule::KeepRelative
							,	false
						)
			);

			this->TileItems.Add(currentItem);

			if (!this->IsActorBeingDestroyed()) 
			{
				currentItem->OnDestroyed.AddDynamic(this, &ARoadTileSection::RemoveItem);
			}
		}
		else 
		{
			this->TileItems.Add(NULL);
		}
		
	}
}

void ARoadTileSection::Init(int dificulty, int dificultyMargin)
{
	this->Dificulty = dificulty;
	this->DificultyMargin = dificultyMargin;
	
	int totalCreated = this->WorldBuilder->GetTotalTilesCreated();
	int initialCount = this->WorldBuilder->TilesCount;

	if (totalCreated > initialCount)
	{
		this->BuildTrails(0);
	}

	this->ItemFactory = Cast<URoadTileItemFactory>( this->ItemFactoryType->GetDefaultObject() );
}

void ARoadTileSection::SetTileBefore(ARoadTileSection* before)
{
	this->Before = before;
}

ARoadTileSection* ARoadTileSection::GetTileBefore()
{
	return this->Before;
}

int ARoadTileSection::GetTrailsCount()
{
	return this->TrailsCount;
}

TArray<AActor*> ARoadTileSection::GetItems()
{
	return this->TileItems;
}


void ARoadTileSection::RemoveItem(AActor* currentItem)
{
	this->TileItems.Remove(currentItem);
}
