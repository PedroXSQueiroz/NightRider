// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <Services/RiderCollideCallback.h>

#include "Multiplier.generated.h"

UCLASS()
class NIGHTRIDER_API AMultiplier : public AActor , public IRiderCollideCallback
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiplier();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MultiplierMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* MultiplierCollision;

	virtual void OnRiderCollide(class ARider* rider) override;

protected:
	
	virtual float GetValue() PURE_VIRTUAL(TEXT("NOT IMPLMENETED YET"), return 0.f; )

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
