// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Tickable.h"

#include "WorldTilesObservable.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UWorldTilesObservable : public UInterface
{

	GENERATED_BODY()

};

UCLASS(Blueprintable)
class WORLDBUILDER_API UWorldTileObserverTicker : public UObject, public FTickableGameObject
{
	
	GENERATED_BODY()

public:
	
	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;

	virtual bool IsTickableWhenPaused() const override;

	virtual bool IsTickableInEditor() const override;

	virtual TStatId GetStatId() const override;

	//class IWorldTilesObservable* Reference;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnTick, float DelteTime)
	FOnTick OnTick() 
	{
		return this->OnTickEvent;
	}

private:

	int LastFrameUpdated = INDEX_NONE;

	FOnTick OnTickEvent = FOnTick();

};

class WORLDBUILDERMODULE_API IWorldTilesObservable  {

	GENERATED_BODY()

public:

	UFUNCTION()
	virtual FVector GetReferencePosition();

	UFUNCTION()
	virtual FVector GetReferenceVelocity();

	UFUNCTION()
	virtual bool IsReference();
	
	FVector* GetReferenceOffset();

	void ResetOffset();

	void UpdateReferenceOffset(float DeltaTime);
	
private:

	FVector* ReferenceOffset;

	UWorldTileObserverTicker* Ticker;

};
