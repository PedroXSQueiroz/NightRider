// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include <Utils/Constants.h>

#include "WorldTileIndexes.generated.h"

USTRUCT(BlueprintType)
struct FWorldTileIndexes
{
	GENERATED_BODY()
public:

	FWorldTileIndexes()
		: X(0)
		, Y(0)
		, Z(0) {}

	FWorldTileIndexes(int x, int y, int z)
		: X(x)
		, Y(y)
		, Z(z) {}

	int X;
	int Y;
	int Z;

	void SetFromMap(TMap<ESingleAxis, int> map) 
	{
		if (map.Contains(ESingleAxis::X)) 
		{
			this->X = map[ESingleAxis::X];
		}

		if (map.Contains(ESingleAxis::Y))
		{
			this->Y = map[ESingleAxis::Y];
		}

		if (map.Contains(ESingleAxis::Z))
		{
			this->Z = map[ESingleAxis::Z];
		}
	}

	bool operator==(const FWorldTileIndexes& Other) const
	{
		return Equals(Other);
	}

	bool Equals(const FWorldTileIndexes& Other) const
	{
		return	this->X == Other.X
			&&	this->Y == Other.Y
			&&	this->Z == Other.Z;
	}

};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FTileIndexes& Thing);
#else // optimize by inlining in shipping and development builds
FORCEINLINE uint32 GetTypeHash(const FWorldTileIndexes& Thing)
{
	uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FWorldTileIndexes));
	return Hash;
}
#endif
