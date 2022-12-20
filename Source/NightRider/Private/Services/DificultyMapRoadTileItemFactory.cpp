// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/DificultyMapRoadTileItemFactory.h"

#include "Math/UnrealMathUtility.h"

#include <Entities/RoadTileSection.h>
#include <Services/Statistcs.h>

TArray<TSubclassOf<AActor>> UDificultyMapRoadTileItemFactory::GetItems(ARoadTileSection* tileTarget)
{
	UWorld* currentWorld		= tileTarget->GetWorld();
	
	int currentPlayerLevel		= UStatistcs::GetCurrentPlayerLevel(currentWorld);

	float distanceRunned		= UStatistcs::GetDistanceRunned(currentWorld);
	
	int totalTrails				= tileTarget->GetTrailsCount();

	ARoadTileSection* tileBefore = tileTarget->GetTileBefore();
	
	int nextFreeTrail = -1;
	
	float totalMaxDificulty = this->MaxDificultyByLavelFactor * distanceRunned;
	totalMaxDificulty = totalMaxDificulty > 100 ? 100 : totalMaxDificulty;
	float totalMinDificulty = this->MinDificultyByLavelFactor * distanceRunned;
	totalMinDificulty = totalMinDificulty > 100 ? 100 : totalMinDificulty;
	
	if (tileBefore) 
	{
		int beforeFreeTrailIndex	= this->FindFreeTrailItem(tileTarget->GetTileBefore());

		float probabilityOfSequentialsFreeTrials = 100 - totalMaxDificulty;

		for (int trailIndex = 0; trailIndex < totalTrails; trailIndex++) 
		{
			int trailProbabilityIndex = FMath::Abs(trailIndex - beforeFreeTrailIndex);

			float probability = (-1 * ( probabilityOfSequentialsFreeTrials - 50 ) * trailProbabilityIndex) + probabilityOfSequentialsFreeTrials;

			bool isTheNextFreeTrail = FMath::RandRange( 0, 100 ) > probability;

			if (isTheNextFreeTrail) 
			{
				nextFreeTrail = trailIndex;
				break;
			}
		}
	}
	

	if (nextFreeTrail == -1) 
	{
		nextFreeTrail = FMath::RandRange(0, totalTrails - 1);
	}

	TArray<TSubclassOf<AActor>> items = TArray<TSubclassOf<AActor>>();

	for (int currentTrailIndex = 0; currentTrailIndex < totalTrails; currentTrailIndex++) 
	{
		if (currentTrailIndex != nextFreeTrail) 
		{
			int dificultyIndex = FMath::Abs(currentTrailIndex - nextFreeTrail);

			float trailMaxDificulty = totalMaxDificulty * dificultyIndex;
			float trailMinDificulty = totalMinDificulty * dificultyIndex;

			float currentDificultyTarget = FMath::RandRange(trailMinDificulty, trailMaxDificulty);

			TArray<TSubclassOf<AActor>> itemTypes = TArray<TSubclassOf<AActor>>();
			
			this->ItemToDificulty.GetKeys(itemTypes);
			


			TArray<TSubclassOf<AActor>> itemsOnPossibilityRange = TArray<TSubclassOf<AActor>>();

			for (TSubclassOf<AActor> itemType : itemTypes) 
			{
				FPossibilityRange itemTypeDificultRange = this->ItemToDificulty[itemType];

				bool itemInRange = ( itemTypeDificultRange.Min < currentDificultyTarget ) && 
									( currentDificultyTarget < itemTypeDificultRange.Max );
									

				if (itemInRange) 
				{
					itemsOnPossibilityRange.Add(itemType);
				}	
			}

			if (itemsOnPossibilityRange.Num() == 0)
			{
				items.Add(NULL);
			}
			else 
			{
				TSubclassOf<AActor> itemType = itemsOnPossibilityRange[FMath::RandRange(0, itemsOnPossibilityRange.Num() - 1)];
				FString typeName;

				itemType->GetName(typeName);
				
				UE_LOG(LogTemp, Log, TEXT("Item type %s for trail: %i section: %i"), *typeName, currentTrailIndex, tileTarget->Index );
				
				items.Add(itemType);
			}
			

		}
		else 
		{
			items.Add(NULL);

			UE_LOG(LogTemp, Log, TEXT("Trail empty: %i section: %i"), currentTrailIndex, tileTarget->Index);
		}
		
	}

	return items;
}

int UDificultyMapRoadTileItemFactory::FindFreeTrailItem(ARoadTileSection* tile)
{
	TArray<AActor*> items = tile->GetItems();

	for (int itemIndex = 0; itemIndex < items.Num(); itemIndex++) 
	{
		if (!items[itemIndex]) 
		{
			return itemIndex;
		}
	}
	
	return 0;
}
