// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <Services/RiderCollideCallback.h>

#include "Obstacle.generated.h"

UCLASS()
class NIGHTRIDER_API AObstacle : public AActor, public IRiderCollideCallback
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ObstacleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* ObstacleCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Dificulty;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
