// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Recycles/ByDistance/WordTileRecycleByDistance.h"

#include "Kismet/GameplayStatics.h"

#include <Services/WorldTileFactory.h>
#include <Services/WorldTilesObservableContainer.h>

#include <Entities/WorldTilesObservable.h>

#include <Dtos/WorldTileIndexes.h>
#include <Dtos/WorldTileParams.h>

#include <Entities/WorldTile.h>

#include <WorldBuilderModule/Public/Components/WorldTileRecycleByDistanceRef.h>

void UWordTileRecycleByDistance::Setup(
		UWorldTileFactory* factory
	,	UWorld* world
	,	IWorldTilesObservable* reference )
{
	this->CurrentTileFactory = factory;
	this->Alignment = this->CurrentTileFactory->GetParams().AxisAlignment;

	this->Reference = reference;
}


bool UWordTileRecycleByDistance::ShouldRecycle(AWorldTile* tile)
{
	if (!tile->CanBeRecycled) 
	{
		return false;
	}
	
	return this->GetCurrentDistanceFromRef(tile) > this->MaxDistanceToSpawn;
}

bool UWordTileRecycleByDistance::CanTileBeRecycled(AWorldTile* tile)
{
	if (!tile->CanBeRecycled) 
	{
		float tileDistance = FVector::Distance(
										tile->GetActorLocation()
									,	this->Reference->GetReferencePosition()
									);
		
		return tileDistance < this->MaxDistanceToSpawn;
	}
	
	return true;
}


FWorldTileIndexes* UWordTileRecycleByDistance::GetNextIndexes(AWorldTile* tile)
{
	
	FWorldTileParams params = this->CurrentTileFactory->GetParams();
	
	FWorldTileIndexes* indexes =  new FWorldTileIndexes();

	switch (params.AxisAlignment)
	{
	case EAxisAlignment::X:
		
		indexes->X =
			this->CurrentTileFactory->GetSymetricIndexes(
				ESingleAxis::X,
				tile->Indexes->X,
				true
			);

		
		break;
	case EAxisAlignment::Y:
		
		indexes->Y =
			this->CurrentTileFactory->GetSymetricIndexes(
				ESingleAxis::Y,
				tile->Indexes->Y,
				true
			);

		
		break;
	case EAxisAlignment::Z:
		
		indexes->Z =
			this->CurrentTileFactory->GetSymetricIndexes(
				ESingleAxis::Z,
				tile->Indexes->Z,
				true
			);
		
		break;
	case EAxisAlignment::XY:
		
		indexes->SetFromMap(
			this->CurrentTileFactory->GetSymetricIndexes(
				ESingleAxis::X,
				tile->Indexes->X,
				ESingleAxis::Y,
				tile->Indexes->Y,
				true
			)
		);
		
		break;
	case EAxisAlignment::XZ:
		
		indexes->SetFromMap(
			this->CurrentTileFactory->GetSymetricIndexes(
				ESingleAxis::X,
				tile->Indexes->X,
				ESingleAxis::Z,
				tile->Indexes->Z,
				true
			)
		);
		
		break;
	case EAxisAlignment::YZ:
		
		indexes->SetFromMap(
			this->CurrentTileFactory->GetSymetricIndexes(
				ESingleAxis::Y,
				tile->Indexes->Y,
				ESingleAxis::Z,
				tile->Indexes->Z,
				true
			)
		);
		
		break;
	case EAxisAlignment::ALL:
		 
		indexes->SetFromMap(
			this->CurrentTileFactory->GetSymetricIndexes(
				ESingleAxis::X,
				tile->Indexes->X,
				ESingleAxis::Y,
				tile->Indexes->Y,
				ESingleAxis::Z,
				tile->Indexes->Z,
				true
			)
		);
		
		break;
	
	default:
		return nullptr;
	}

	return indexes;
}

float UWordTileRecycleByDistance::GetCurrentDistanceFromRef(AWorldTile* tile)
{
	FVector referencePos = this->Reference->GetReferencePosition();
	FVector tilePos = tile->GetActorLocation();

	switch (this->Alignment)
	{
	case EAxisAlignment::X:
		return this->Distance(referencePos.X, tilePos.X);
	case EAxisAlignment::Y:
		return this->Distance(referencePos.Y, tilePos.Y);
	case EAxisAlignment::Z:
		return this->Distance(referencePos.Z, tilePos.Z);

	case EAxisAlignment::XY:
		return this->Distance( 
			FVector2D( 
				referencePos.X
			,	referencePos.Y)
			, FVector2D(
				tilePos.X
			,	tilePos.Y
			)
		);
	case EAxisAlignment::XZ:
		return this->Distance(
			FVector2D(
				referencePos.X
			,	referencePos.Z)
			, FVector2D(
				tilePos.X
			,	tilePos.Z
			)
		);
	
	case EAxisAlignment::YZ:
		return this->Distance(
			FVector2D(
				referencePos.Y
			,	referencePos.Z)
			, FVector2D(
				tilePos.Y
			,	tilePos.Z
			)
		);
	
	case EAxisAlignment::ALL:
		return this->Distance(referencePos, tilePos);

	}

	return 0;
}

float UWordTileRecycleByDistance::Distance(float start, float end)
{
	return FMath::Abs( end - start );
}

float UWordTileRecycleByDistance::Distance(FVector2D start, FVector2D end)
{
	return FMath::Abs( FVector2D::Distance( end, start ) );
}

float UWordTileRecycleByDistance::Distance(FVector start, FVector end)
{
	return FMath::Abs( FVector::Distance( end, start ) );
}
