// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESingleAxis : uint8 {
	X = 0,
	Y = 1,
	Z = 2
};

UENUM(BlueprintType)
enum class EAxisAlignment : uint8 {

	X = 0,
	Y = 1,
	Z = 2,
	XY = 3,
	XZ = 4,
	YZ = 5,
	ALL = 6
};


/**
 * 
 */
class Constants
{

};
