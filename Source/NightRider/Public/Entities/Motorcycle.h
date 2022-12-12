// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Motorcycle.generated.h"

UCLASS()
class NIGHTRIDER_API AMotorcycle : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMotorcycle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MotorcycleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RelativePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RelativeRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RelativeScale;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
