// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/WorldTileFactory.h"

#include <Entities/WorldTile.h>
#include <Entities/WorldTileMeshData.h>
#include <Entities/WorldTileItemData.h>
#include <Entities/WorldTilesObservable.h>

#include <Services/WorldTileMeshFactory.h>
#include <Services/WorldTileItemsFactory.h>
#include <Services/WordTileRecycle.h>

#include <Dtos/WorldTileIndexes.h>
#include <Dtos/WorldTileParams.h>

#include <Utils/Constants.h>
#include <Services/WorldTilesObservableContainer.h>

void UWorldTileFactory::Setup(UWorld* world)
{
	//this->Params = this->ParamsType.GetDefaultObject();
	this->Recycle = this->Params.RecycleType.GetDefaultObject();


	this->CurrentWorldReference = world;
	this->ObservableContainer = this->ObservableContainerType.GetDefaultObject();

	this->ObservableReference = Cast<IWorldTilesObservable>(this->ObservableContainer->GetReference(world).GetObject());

	IWorldTilesObservable* reference = Cast<IWorldTilesObservable>( 
															this->ObservableContainer
																->GetReference(world)
																.GetObjectRef() 
														);

	this->Recycle->Setup(this, world, reference);

	if (this->XIndexesTracking) 
	{
		this->XIndexesTracking->Empty();
	}

	if (this->YIndexesTracking) 
	{
		this->YIndexesTracking->Empty();
	}

	if (this->ZIndexesTracking) 
	{
		this->ZIndexesTracking->Empty();
	}
}

AWorldTile* UWorldTileFactory::Build(
		int xIndex
	,	int yIndex
	,	int zIndex
	,	UWorld* world
	,	float DeltaTime
	,	FVector* offset
)
{
	FWorldTileIndexes* indexes = new FWorldTileIndexes(xIndex, yIndex, zIndex);

	FVector position = this->CalcLocationByIndexes(this->Params, indexes, DeltaTime);

	position.X += offset->X;
	position.Y += offset->Y;
	position.Z += offset->Z;

	AWorldTile* currentTile = world->SpawnActor<AWorldTile>(
		this->Params.WorldTileType,
		FTransform(position)
	);

	UE_LOG(LogTemp, Log, 
			TEXT(" [SPAWNED] Indexes: X=%i;Y=%i;Z=%i Coord: X=%.2f;Y=%.2f;Z=%.2f")
		,	xIndex
		,	yIndex
		,	zIndex
		,	position.X
		,	position.Y
		,	position.Z
	);

	return this->SetupTile(currentTile, indexes, world);
}

AWorldTile* UWorldTileFactory::Build(
		int xIndex
	,	int yIndex
	,	int zIndex
	,	UWorld* world
)
{
	FWorldTileIndexes* indexes = new FWorldTileIndexes(xIndex, yIndex, zIndex);

	FVector position = this->CalcLocationByIndexes(this->Params, indexes, 0);

	AWorldTile* currentTile = world->SpawnActor<AWorldTile>(
		this->Params.WorldTileType,
		FTransform(position)
		);

	return this->SetupTile(currentTile, indexes, world);
}

AWorldTile* UWorldTileFactory::SetupTile(AWorldTile* currentTile, FWorldTileIndexes* indexes, UWorld* world)
{
	currentTile->SizeX = this->Params.SizeX;
	currentTile->SizeY = this->Params.SizeY;
	currentTile->SizeZ = this->Params.SizeZ;
	currentTile->Indexes = indexes;
	currentTile->RelativeMovement = this->Params.RelativeMovement;


	UWorldTileMeshFactory* meshFactory = this->Params.MeshFactoryType.GetDefaultObject();
	TArray<UWorldTileMeshData*> currentTileMeshes = meshFactory->BuildMeshForTile(currentTile);

	for (UWorldTileMeshData* currentMesh : currentTileMeshes)
	{
		currentTile->AttachMesh(currentMesh);
	}


	UWorldTileItemsFactory* itemsFactory = this->Params.ItemsFactoryType.GetDefaultObject();

	TArray<UWorldTileItemData*> currentTileItems = itemsFactory->BuildItemForTile(currentTile);

	for (UWorldTileItemData* currentItem : currentTileItems)
	{
		currentTile->AttachItem(currentItem);
	}


	currentTile->Recycle = this->Recycle;

	currentTile->Reference = this->ObservableReference;
	
	currentTile->Builder = this;

	this->UpdateIndexesTracking(indexes);

	this->OnWorldTileCreated().Broadcast(currentTile);

	return currentTile;
}

int UWorldTileFactory::GetSymetricIndexes(ESingleAxis axis, int index, bool project)
{
	
	TArray<int>* tracking = this->GetTracking(axis);

	int minIndex = ( *tracking )[0];
	int maxIndex = ( *tracking )[tracking->Num() - 1];

	int range = this->GetRangeBetweenIndexes(minIndex, maxIndex);

	int medianIndex = this->GetMedianBetweenIndex(minIndex, maxIndex);

	int distanceFromMedian = FMath::Abs( index - medianIndex ) - 1;
	
	int newIndex = medianIndex;

	if (index > medianIndex) 
	{
		newIndex = medianIndex - distanceFromMedian;

		if (newIndex > minIndex && this->Params.SpawnNewTileOnlyOnBorders) 
		{
			newIndex = minIndex;
		}

		if (project) 
		{
			newIndex -= 1;
		}
	}
	else if (index < medianIndex) 
	{
		newIndex = medianIndex + distanceFromMedian;
		
		if (newIndex < maxIndex && this->Params.SpawnNewTileOnlyOnBorders)
		{
			newIndex = maxIndex;
		}
		
		if (project) 
		{
			newIndex += 1;
		}

	}
	

	UE_LOG(LogTemp, Log, 
		TEXT(" [RECYCLING] Removing: %i; Last: %i; First: %i; MedianIndex: %i, New Index, %i")
	,	index
	,	minIndex
	,	maxIndex
	,	medianIndex
	,	newIndex
	);

	return newIndex;

}

TMap<ESingleAxis, int> UWorldTileFactory::GetSymetricIndexes(
		ESingleAxis firstAxis
	,	int firstIndex
	,	ESingleAxis secondAxis
	,	int secondIndex
	,	bool project)
{
	TMap<ESingleAxis, int> result = TMap<ESingleAxis, int>();
	
	result.Add(firstAxis, this->GetSymetricIndexes(firstAxis, firstIndex, project));
	result.Add(secondAxis, this->GetSymetricIndexes(secondAxis, secondIndex, project));

	return result;
}

TMap<ESingleAxis, int> UWorldTileFactory::GetSymetricIndexes(
		ESingleAxis firstAxis
	,	int firstIndex
	,	ESingleAxis secondAxis
	,	int secondIndex
	,	ESingleAxis thirdAxis
	,	int thirdIndex
	,	bool project)
{
	TMap<ESingleAxis, int> result = TMap<ESingleAxis, int>();

	result.Add(firstAxis, this->GetSymetricIndexes(firstAxis, firstIndex, project));
	result.Add(secondAxis, this->GetSymetricIndexes(secondAxis, secondIndex, project));
	result.Add(thirdAxis, this->GetSymetricIndexes(thirdAxis, thirdIndex, project));

	return result;
}

FWorldTileParams UWorldTileFactory::GetParams()
{
	return FWorldTileParams::Copy( &( this->Params ) );
}

void UWorldTileFactory::RemoveTile(AWorldTile* tile)
{
	UE_LOG(LogTemp, Log, TEXT("REMOVING TILE"));
	this->Tiles.Remove(tile->Indexes);
	this->UpdateIndexesTracking(tile->Indexes, false);
	tile->RecursiveDestroy();
}

void UWorldTileFactory::UpdateIndexesTracking(FWorldTileIndexes* indexes, bool isInserting)
{
	EAxisAlignment currentAlignment = this->Params.AxisAlignment;
	
	switch (currentAlignment) 
	{
		case EAxisAlignment::X:
			UpdateIndexesTracking(ESingleAxis::X, indexes->X, isInserting);
			break;
		case EAxisAlignment::Y:
			UpdateIndexesTracking(ESingleAxis::Y, indexes->Y, isInserting);
			break;
		case EAxisAlignment::Z:
			UpdateIndexesTracking(ESingleAxis::Z, indexes->Z, isInserting);
			break;
		case EAxisAlignment::XY:
			UpdateIndexesTracking(ESingleAxis::X, indexes->X, isInserting);
			UpdateIndexesTracking(ESingleAxis::Y, indexes->Y, isInserting);
			break;
		case EAxisAlignment::XZ:
			UpdateIndexesTracking(ESingleAxis::X, indexes->X, isInserting);
			UpdateIndexesTracking(ESingleAxis::Z, indexes->Z, isInserting);
			break;
		case EAxisAlignment::YZ:
			UpdateIndexesTracking(ESingleAxis::Y, indexes->Y, isInserting);
			UpdateIndexesTracking(ESingleAxis::Z, indexes->Z, isInserting);
			break;
		case EAxisAlignment::ALL:
			UpdateIndexesTracking(ESingleAxis::X, indexes->X, isInserting);
			UpdateIndexesTracking(ESingleAxis::Y, indexes->Y, isInserting);
			UpdateIndexesTracking(ESingleAxis::Z, indexes->Z, isInserting);
			break;
	}

}

void UWorldTileFactory::UpdateIndexesTracking(ESingleAxis axis, int index, bool isInserting)
{
	TArray<int>* trackingToUpdate = this->GetTracking(axis);
	
	if (isInserting && !trackingToUpdate->Contains(index))
	{
		trackingToUpdate->Add(index);
	}
	else if(!isInserting && trackingToUpdate->Contains(index))
	{
		trackingToUpdate->Remove(index);
	}

	trackingToUpdate->Sort();
}

TArray<int>* UWorldTileFactory::GetTracking(ESingleAxis axis)
{
	switch (axis)
	{
		case ESingleAxis::X:
		
			if (!this->XIndexesTracking) 
			{
				this->XIndexesTracking = new TArray<int>();
			}

			return this->XIndexesTracking;

		case ESingleAxis::Y:
		
			if (!this->YIndexesTracking)
			{
				this->YIndexesTracking = new TArray<int>();
			}

			return this->YIndexesTracking;

		case ESingleAxis::Z:
		
			if (!this->ZIndexesTracking)
			{
				this->ZIndexesTracking = new TArray<int>();
			}

			return this->ZIndexesTracking;

		default:
			return nullptr;
	}
}

FVector UWorldTileFactory::CalcLocationByIndexes(FWorldTileParams currentParams, FWorldTileIndexes* indexes, float DeltaTime)
{
	float xPosition =
			currentParams.AxisAlignment == EAxisAlignment::X
		||	currentParams.AxisAlignment == EAxisAlignment::XY
		||	currentParams.AxisAlignment == EAxisAlignment::XZ
		||	currentParams.AxisAlignment == EAxisAlignment::ALL
		? (	currentParams.SizeX * indexes->X) - (currentParams.SizeX / 2) :
		0;

	float yPosition =
			currentParams.AxisAlignment == EAxisAlignment::Y
		||	currentParams.AxisAlignment == EAxisAlignment::XY
		||	currentParams.AxisAlignment == EAxisAlignment::YZ
		||	currentParams.AxisAlignment == EAxisAlignment::ALL
		? (	currentParams.SizeY * indexes->Y) - (currentParams.SizeY / 2) :
		0;

	float zPosition =
			currentParams.AxisAlignment == EAxisAlignment::Z
		||	currentParams.AxisAlignment == EAxisAlignment::XZ
		||	currentParams.AxisAlignment == EAxisAlignment::YZ
		||	currentParams.AxisAlignment == EAxisAlignment::ALL
		? (	currentParams.SizeZ * indexes->Z) - (currentParams.SizeZ / 2) :
		0;

	FVector position = FVector(xPosition, yPosition, zPosition);

	if (currentParams.RelativeMovement) 
	{
		IWorldTilesObservable* reference = Cast<IWorldTilesObservable>(
																this->ObservableContainer
																->GetReference(this->CurrentWorldReference)
																.GetObjectRef()
															);
		position += ( reference->GetReferenceVelocity() * -1 ) * DeltaTime;
	}

	return position;
}

int UWorldTileFactory::GetRangeBetweenIndexes(int minIndex, int maxIndex)
{
	if (minIndex > 0 && maxIndex > 0)
	{
		return maxIndex - minIndex;
	}
	else if (minIndex < 0 && maxIndex > 0)
	{
		return (maxIndex + FMath::Abs(minIndex));
	}
	else if (minIndex < 0 && maxIndex < 0)
	{
		return (maxIndex + FMath::Abs(minIndex));
	}

	// PROBABLY THE ARRAY IS ON THE WRONG ORDER
	// SHOULD RAISE EXCEPTION
	return 0;
}

int UWorldTileFactory::GetMedianBetweenIndex(int minIndex, int maxIndex) 
{
	
	if (minIndex > maxIndex) 
	{
		int aux = minIndex;
		minIndex = maxIndex;
		maxIndex = aux;
	}

	int range = maxIndex - minIndex;

	float median = 0;

	if (range % 2 == 0) 
	{
		median = range / 2;
	}
	else
	{
		median = (range + 1) / 2;
	}

	UE_LOG(LogTemp, Log, TEXT("Min: %i, Max: %i, Median: %f"), minIndex, maxIndex, median);

	return FMath::FloorToInt( minIndex + median );
	


	//int range = 0;
	//
	//if (minIndex > 0 && maxIndex > 0)
	//{
	//	range = this->GetRangeBetweenIndexes(minIndex, maxIndex);
	//	return ((float)range) / 2.f;
	//}
	//else if (minIndex < 0 && maxIndex > 0)
	//{
	//	range = this->GetRangeBetweenIndexes(minIndex, maxIndex);
	//	return ((float)range / 2.f) - FMath::Abs(minIndex);
	//}
	//else if (minIndex < 0 && maxIndex < 0)
	//{
	//	range = this->GetRangeBetweenIndexes(minIndex, maxIndex);
	//	return ((float)range / 2.f) - FMath::Abs(minIndex);
	//}
	//
	//
	///*if (minIndex > 0 && maxIndex > 0)
	//{
	//	return maxIndex - minIndex;
	//}
	//else if (minIndex < 0 && maxIndex > 0)
	//{
	//	return (maxIndex + FMath::Abs(minIndex));
	//}
	//else if (minIndex < 0 && maxIndex < 0)
	//{
	//	return (maxIndex + FMath::Abs(minIndex));
	//}*/

	//// PROBABLY THE ARRAY IS ON THE WRONG ORDER
	//// SHOULD RAISE EXCEPTION
	//return 0;
}
