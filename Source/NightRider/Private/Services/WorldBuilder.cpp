// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/WorldBuilder.h"

#include <Entities/TileSection.h>
#include <Entities/Rider.h>
#include <Services/RelativeVelocityComponent.h>
#include <Services/RelativeVelocityObserverComponent.h>

// Sets default values for this component's properties
UWorldBuilder::UWorldBuilder()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	this->Tiles = TArray<ATileSection*>();
	
	// ...
}

void UWorldBuilder::init(UWorld* world)
{
	this->CurrentWorldReference = world;
}

void UWorldBuilder::SpawnNextTileSection(float velocityCompensation)
{
	float defaultSizeX = this->SectionType.GetDefaultObject()->SizeX;

	ATileSection* newTile = this->CurrentWorldReference->SpawnActor<ATileSection>(
																			this->SectionType, 
																			FTransform(
																					this->GetNextTilePosition(defaultSizeX) 
																				-	FVector(velocityCompensation, 0, 0)
																			) 
																		);
	newTile->Index = this->Tiles.Num();
	newTile->SetWorldBuilder(this);
	newTile->Init(0, 0);
	
	if (newTile) 
	{
		newTile->SetReference(this->CurrentReference);
		newTile->SetMaxDistanceFromReference(100);
	
		this->CurrentReference->RelativeVelocityReference->RegisterObserver(newTile);

		int tileIndex = this->Tiles.Add(newTile);

		if (tileIndex > 0) 
		{
			ATileSection* previousTile = this->Tiles[tileIndex - 1];
			previousTile->Before = previousTile;
		}
	}

	if (URelativeVelocityObserverComponent* observer = this->GetObserverFromTileSection(newTile)) 
	{
		observer->SetWorldBuilderOrigin(this);
	}
	
	this->TotalTilesCreated++;
}

void UWorldBuilder::SpawnInitialSections()
{
	this->Tiles.Empty();
	this->TotalTilesCreated = 0;
	
	for (int sectionIndex = 0; sectionIndex < this->TilesCount; sectionIndex++)  
	{
		this->SpawnNextTileSection(0);
	}

	this->SetupBorderSection();
}


void UWorldBuilder::SetRider(ARider* rider)
{
	this->CurrentReference = rider;
}

void UWorldBuilder::CycleForward(float velocityCompensation)
{
	ATileSection* lastSection = this->Tiles[0];
	this->Tiles.RemoveAt(0);
	lastSection->RecursiveDestroy();

	this->SpawnNextTileSection(velocityCompensation);

	this->SetupBorderSection();
}

int UWorldBuilder::GetTotalTilesCreated()
{
	return this->TotalTilesCreated;
}

void UWorldBuilder::RemoveTile(ATileSection* tile)
{
	this->Tiles.Remove(tile);
}

FVector UWorldBuilder::GetNextTilePosition(float sectionXSize)
{
	if (this->Tiles.IsEmpty())
	{
		float tileSizeMedian = sectionXSize / 2.f;

		float initialDealocation = 
			(
				(
				this->TilesCount % 2 == 0 ?
					(((this->TilesCount - 1) / 2.f) * sectionXSize)
				:	(this->TilesCount / 2.f) * sectionXSize
				) * -1 
			) + tileSizeMedian;
		
		return FVector(initialDealocation, 0, 0);
	}
	else
	{
		ATileSection* lastTile = this->Tiles.Last();
		FVector lastTileLocation = lastTile->GetActorLocation();
		lastTileLocation.X += lastTile->SizeX;

		return lastTileLocation;
	}
}

URelativeVelocityObserverComponent* UWorldBuilder::GetObserverFromTileSection(ATileSection* section)
{
	UActorComponent* observerInstance = section->GetComponentByClass(URelativeVelocityObserverComponent::StaticClass());

	if (observerInstance)
	{
		URelativeVelocityObserverComponent* observer = Cast<URelativeVelocityObserverComponent>(observerInstance);
		return observer;
	}

	return NULL;
}

void UWorldBuilder::SetupBorderSection() 
{
	ATileSection* lastSection = this->Tiles[0];
	
	int medianSectionIndex = FMath::CeilToInt(this->Tiles.Num() / 2.f);

	float intermediaryRoadLength = 0;
	for (int currentSectionIndex = medianSectionIndex - 1; currentSectionIndex > 1; currentSectionIndex--)
	{
		ATileSection* currentTileSection = this->Tiles[currentSectionIndex];
		intermediaryRoadLength += currentTileSection->SizeX;
	}

	ATileSection* mediaSection = this->Tiles[medianSectionIndex];
	ATileSection* currentLastSection = this->Tiles[0];
	float maxDistance = (lastSection->SizeX + (mediaSection->SizeX / 2.f) + intermediaryRoadLength);

	if (URelativeVelocityObserverComponent* observer = this->GetObserverFromTileSection(currentLastSection))
	{
		observer->SetIsBorder(true);
		observer->SetMaxDistanceFromReference(maxDistance);
	}
}