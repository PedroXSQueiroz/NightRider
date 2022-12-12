// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "RiderCollideCallback.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class URiderCollideCallback : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class NIGHTRIDER_API IRiderCollideCallback
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void OnRiderCollide(class ARider* rider);
};