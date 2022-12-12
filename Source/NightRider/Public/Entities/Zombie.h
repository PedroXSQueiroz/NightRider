// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Zombie.generated.h"

UCLASS()
class NIGHTRIDER_API AZombie : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombie();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* ZombieBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* ZombieCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Dificulty;

	bool GetIsDead();
	
	void OnShooted();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsDead = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
