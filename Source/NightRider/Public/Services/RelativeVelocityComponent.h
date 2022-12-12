// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RelativeVelocityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NIGHTRIDER_API URelativeVelocityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URelativeVelocityComponent();

	void SetVelocity(FVector vel);

	void RegisterObserver(AActor* observer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<AActor*> Observers;

	FVector CurrentVelocity;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
