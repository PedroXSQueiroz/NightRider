// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <Utils/Constants.h>
#include <Dtos/WorldTileIndexes.h>

#include "WorldTile.generated.h"

UCLASS()
class WORLDBUILDERMODULE_API AWorldTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldTile();



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SizeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SizeZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UStaticMeshComponent*> TileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAxisAlignment Axis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AActor*> TileItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWorldTileItemsFactory> ItemFactoryType;

	class IWorldTilesObservable* Reference;

	bool RelativeMovement;

	class UWordTileRecycle* Recycle;

	void AttachMesh(class UWorldTileMeshData* meshData);

	void AttachItem(class UWorldTileItemData* itemData);

	void RemoveItem(AActor* item);

	bool IsInArea(FVector checkPosition);
	
	bool CanBeRecycled;

	FWorldTileIndexes* Indexes;

	UFUNCTION(BlueprintGetter)
	FWorldTileIndexes GetIndexes() 
	{
		if (this->Indexes) 
		{
			return *this->Indexes;
		}

		return FWorldTileIndexes();
	}

	class UWorldTileFactory* Builder;

	void RecursiveDestroy();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};