// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/WorldTile.h"

#include <Entities/WorldTileMeshData.h>
#include <Entities/WorldTileItemData.h>
#include <Entities/WorldTilesObservable.h>

#include <Services/WorldTilesObservableContainer.h>
#include <Services/WorldTileFactory.h>
#include <Services/WordTileRecycle.h>
#include <Services/WorldTileItemsFactory.h>

#include <Dtos/WorldTileIndexes.h>

// Sets default values
AWorldTile::AWorldTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AWorldTile::AttachMesh(UWorldTileMeshData* meshData)
{
	UStaticMeshComponent* meshComponent = NewObject<UStaticMeshComponent>(this);
	meshComponent->SetStaticMesh(meshData->Mesh);
	meshComponent->SetRelativeTransform(meshData->RelativeFransform);
	meshComponent->RegisterComponent();
	meshComponent->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepRelativeTransform );
	
}

void AWorldTile::AttachItem(UWorldTileItemData* itemData)
{
	itemData->Item->AttachToActor(
		this
		, FAttachmentTransformRules(
			EAttachmentRule::KeepWorld
			, EAttachmentRule::KeepRelative
			, EAttachmentRule::KeepRelative
			, false
		)
	);

	if (!this->IsActorBeingDestroyed())
	{
		itemData->Item->OnDestroyed.AddDynamic(this, &AWorldTile::RemoveItem);
	}

	this->TileItems.Add(itemData->Item);
}

void AWorldTile::RemoveItem(AActor* item)
{
	this->TileItems.Remove(item);
}

bool AWorldTile::IsInArea(FVector checkPosition)
{
	FVector roadTileLocation = this->GetActorLocation();

	float currentRoadTileXMedian = this->SizeX / 2;
	float currentRoadTileYMedian = this->SizeY / 2;
	float currentRoadTileZMedian = this->SizeZ / 2;

	
	float currentRoadTileInitialX	= roadTileLocation.X - currentRoadTileXMedian;
	float currentRoadTileFinalX		= roadTileLocation.X + currentRoadTileXMedian;
	
	float currentRoadTileInitialY	= roadTileLocation.Y - currentRoadTileXMedian;
	float currentRoadTileFinalY		= roadTileLocation.Y + currentRoadTileXMedian;
	
	float currentRoadTileInitialZ	= roadTileLocation.Y - currentRoadTileXMedian;
	float currentRoadTileFinalZ		= roadTileLocation.Y + currentRoadTileXMedian;


	return	currentRoadTileInitialX < checkPosition.X	&&	checkPosition.X < currentRoadTileFinalX
		&&	currentRoadTileInitialY < checkPosition.Y	&&	checkPosition.Y < currentRoadTileFinalY
		&&	currentRoadTileInitialZ < checkPosition.Z	&&	checkPosition.Z < currentRoadTileFinalZ;
}

// Called when the game starts or when spawned
void AWorldTile::BeginPlay()
{
	Super::BeginPlay();

	UWorldTileItemsFactory* itemFactory = this->ItemFactoryType.GetDefaultObject();
	TArray<UWorldTileItemData*> currentTileItems = itemFactory->BuildItemForTile(this);
	for (UWorldTileItemData* currentItem : currentTileItems)
	{
		this->AttachItem(currentItem);
	}

}

// Called every frame
void AWorldTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->RelativeMovement) 
	{
		FVector referenceVelocity = this->Reference->GetReferenceVelocity();
		this->SetActorLocation( this->GetActorLocation() + ( ( referenceVelocity * -1 )  * DeltaTime ) );
	}

	/*if (this->Reference->IsReference()) 
	{
		this->Reference->UpdateReferenceOffset( DeltaTime );
	}*/

	this->CanBeRecycled = this->Recycle->CanTileBeRecycled(this);

	if ( this->CanBeRecycled && this->Recycle->ShouldRecycle(this) ) 
	{
		UE_LOG(LogTemp, Log, TEXT("RECYCLING"));
		
		FWorldTileIndexes* nextTileIndexes = this->Recycle->GetNextIndexes(this);

		if (this->Reference->IsReference()) 
		{
			this->Builder->Build(
					nextTileIndexes->X
				,	nextTileIndexes->Y
				,	nextTileIndexes->Z
				,	this->GetWorld()
				,	DeltaTime
				,	this->Reference->GetReferenceOffset()
			);
		}
		else
		{
			this->Builder->Build(
					nextTileIndexes->X
				,	nextTileIndexes->Y
				,	nextTileIndexes->Z
				,	this->GetWorld()
			);
		}

		this->Builder->RemoveTile(this);
	}

}

void AWorldTile::RecursiveDestroy()
{
	for (AActor* currentItem : this->TileItems)
	{
		if (currentItem)
		{
			currentItem->ConditionalBeginDestroy();
			currentItem->Destroy();
		}
	}

	this->ConditionalBeginDestroy();
	this->Destroy();
}
