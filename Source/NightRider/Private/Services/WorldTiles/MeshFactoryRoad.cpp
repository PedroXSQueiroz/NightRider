// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/WorldTiles/MeshFactoryRoad.h"

#include <WorldBuilderModule/Public/Entities/WorldTile.h>
#include <WorldBuilderModule/Public/Entities/WorldTileMeshData.h>


TArray<UWorldTileMeshData*> UMeshFactoryRoad::BuildMeshForTile(AWorldTile* tile)
{
	TArray<UWorldTileMeshData*> meshes = TArray<UWorldTileMeshData*>();

	UWorldTileMeshData* currentMeshData = NewObject<UWorldTileMeshData>();
	currentMeshData->Mesh = this->GroundRoadMesh;
	currentMeshData->RelativeFransform = FTransform(this->GroundRoadPosition);
	
	meshes.Add(currentMeshData);
	
	return meshes;
}
