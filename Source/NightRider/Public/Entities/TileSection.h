// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileSection.generated.h"

UCLASS()
class NIGHTRIDER_API ATileSection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileSection();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SizeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* TileMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class URelativeVelocityObserverComponent> ReferenceObserverType;

	class URelativeVelocityObserverComponent* ReferenceObserver;

	void SetWorldBuilder(class UWorldBuilder* builder);

	void SetMaxDistanceFromReference(float distance);

	void SetReference(AActor* reference);

	TArray<AActor*> TileItems;

	virtual void Init(int dificulty, int dificultyMargiin) PURE_VIRTUAL(TEXT("DOES NOTHING YET"));

	void RecursiveDestroy();

	bool IsCurrentTileAreaOverTheCenter();

	ATileSection* Before;

	int Index;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	float MaxDistanceFromReference;
	class UWorldBuilder* WorldBuilder;
	class AActor* Reference;

	//FIXME: THIS SHOULD NOT BE HERE
	int Dificulty;
	int DificultyMargin;

private:

	bool IsOverTheCenter;
	bool PassedThroughCenter;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
