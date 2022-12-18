// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <Entities/Cash.h>

#include "CashByDificult.generated.h"

UCLASS()
class NIGHTRIDER_API ACashByDificult : public ACash
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACashByDificult();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual int GetAmmount() override;
};
