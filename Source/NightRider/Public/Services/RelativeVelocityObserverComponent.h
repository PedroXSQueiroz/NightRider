// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RelativeVelocityObserverComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NIGHTRIDER_API URelativeVelocityObserverComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	URelativeVelocityObserverComponent();
	
	virtual void OnUpdateDistanceToRferenceUpdate(float newDistance, float distanceDealocated, float atTime);
	
	void SetMaxDistanceFromReference(float distance);

	void SetIsBorder(bool isBorder);

	void SetWorldBuilderOrigin(class UWorldBuilder* origin);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	float MaxDistanceFromRefeence;

	bool IsBorder;

	class UWorldBuilder* WorldBuilderOrigin;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
