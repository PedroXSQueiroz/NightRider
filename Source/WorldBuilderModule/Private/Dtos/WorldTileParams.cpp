// Fill out your copyright notice in the Description page of Project Settings.


#include "Dtos/WorldTileParams.h"

#include <Entities/WorldTile.h>
#include <Services/WorldTileMeshFactory.h>
#include <Services/WorldTileItemsFactory.h>
#include <Services/WordTileRecycle.h>

FWorldTileParams FWorldTileParams::Copy(FWorldTileParams* params)
{
    FWorldTileParams copy = FWorldTileParams();
    
    copy.SizeX              = params->SizeX;
    copy.SizeY              = params->SizeY;
    copy.SizeZ              = params->SizeZ;
    copy.MeshFactoryType    = params->MeshFactoryType;
    copy.ItemsFactoryType   = params->ItemsFactoryType;
    copy.RecycleType        = params->RecycleType;
    copy.AxisAlignment      = params->AxisAlignment;

    return copy;
}
