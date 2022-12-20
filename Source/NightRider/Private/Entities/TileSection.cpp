// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/TileSection.h"

#include <Kismet/GameplayStatics.h>

#include <Services/WorldBuilder.h>
#include <Services/RelativeVelocityObserverComponent.h>
#include <Services/Statistcs.h>
#include <NightRider/NightRiderGameMode.h>

// Sets default values
ATileSection::ATileSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TILE_MESH"));
}

// Called when the game starts or when spawned
void ATileSection::BeginPlay()
{
	Super::BeginPlay();

	this->ReferenceObserver = NewObject<URelativeVelocityObserverComponent>( this, this->ReferenceObserverType );
	this->ReferenceObserver->RegisterComponent();
}

void ATileSection::RemoveFromWorldBuilder() 
{
	if (this->WorldBuilder)
	{
		this->WorldBuilder->RemoveTile(this);
	}

	this->shouldRemove = true;
}

void ATileSection::FinishDestroy()
{
	this->RemoveFromWorldBuilder();

	Super::FinishDestroy();
}

void ATileSection::SetWorldBuilder(UWorldBuilder* worldBuilder)
{
	this->WorldBuilder = worldBuilder;

	if (this->shouldRemove) 
	{
		this->RemoveFromWorldBuilder();
	}
}

void ATileSection::SetMaxDistanceFromReference(float distance) 
{
	this->MaxDistanceFromReference = distance;
}

void ATileSection::SetReference(AActor* reference) 
{
	this->Reference = reference;
}

// Called every frame
void ATileSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->IsOverTheCenter && !this->IsCurrentTileAreaOverTheCenter())
	{
		this->PassedThroughCenter = true;
		this->IsOverTheCenter = false;

		if (this->TileItems.Num() > 0) 
		{
			UStatistcs::RegisterBarrierPerfectallyDodged(this->GetWorld());
		}

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Passed through center"));
	}
	else
	{
		this->IsOverTheCenter = this->IsCurrentTileAreaOverTheCenter();
	}
	
}

void ATileSection::RecursiveDestroy() 
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

bool ATileSection::IsCurrentTileAreaOverTheCenter()
{
	float xMedian = this->SizeX / 2;

	FVector currentTileLocation = this->GetActorLocation();

	float start = currentTileLocation.X - xMedian;
	float end = currentTileLocation.X + xMedian;
	
	return start < 0 && end > 0;
}

