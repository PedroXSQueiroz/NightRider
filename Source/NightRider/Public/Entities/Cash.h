// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <Services/RiderCollideCallback.h>

#include "Cash.generated.h"

UCLASS()
class NIGHTRIDER_API ACash : public AActor, public IRiderCollideCallback
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACash();

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	class UStaticMeshComponent* CashMesh;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	class UBoxComponent* Collision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnRiderCollide(class ARider* rider) override;

	virtual int GetAmmount() PURE_VIRTUAL(TEXT("NOT IMPLEMENTED YET"), return 0; );

};
