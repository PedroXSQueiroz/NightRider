// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WorldBuilder.generated.h"


UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class NIGHTRIDER_API UWorldBuilder : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWorldBuilder();

	void init(UWorld* world);

	void SpawnNextTileSection(float velocityCompensation);

	void SpawnInitialSections();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TilesCount;

	void SetRider(class ARider* rider);

	void CycleForward(float velocityCompensation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ATileSection> SectionType;

	int GetTotalTilesCreated();

protected:
	
	TArray<class ATileSection*> Tiles;

	FVector GetNextTilePosition(float sectionYSize);

	class ARider* CurrentReference;

	UWorld* CurrentWorldReference;

	class URelativeVelocityObserverComponent* GetObserverFromTileSection(class ATileSection* section);

	void SetupBorderSection();

	int TotalTilesCreated = 0;
		
};
