// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/RelativeVelocityObserverComponent.h"
#include "RoadDistanceObserver.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTRIDER_API URoadDistanceObserver : public URelativeVelocityObserverComponent
{
	GENERATED_BODY()

public:

	virtual void OnUpdateDistanceToRferenceUpdate(float distance, float distanceDealocated, float atTime) override;

};
