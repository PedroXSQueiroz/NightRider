// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/RelativeVelocityComponent.h"

#include <Services/RelativeVelocityObserverComponent.h>

// Sets default values for this component's properties
URelativeVelocityComponent::URelativeVelocityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	this->Observers = TArray<AActor*>();

	// ...
}

void URelativeVelocityComponent::SetVelocity(FVector vel)
{
	this->CurrentVelocity = vel;
}

void URelativeVelocityComponent::RegisterObserver(AActor* observer)
{
	this->Observers.Add(observer);
}


// Called when the game starts
void URelativeVelocityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URelativeVelocityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector currentVelocityReference = this->CurrentVelocity * -1;

	TArray<AActor*> toRemove = TArray<AActor*>();

	for (AActor* currentActorObserver : this->Observers) 
	{
		
		if (currentActorObserver->IsActorBeingDestroyed()) 
		{
			toRemove.Add(currentActorObserver);
		}
		else 
		{
			FVector originalObserverLocation = currentActorObserver->GetActorLocation();
			currentActorObserver->SetActorLocation(currentVelocityReference + originalObserverLocation);
			
			UActorComponent* component = currentActorObserver->GetComponentByClass(URelativeVelocityObserverComponent::StaticClass());
		
			if (component) 
			{
				URelativeVelocityObserverComponent* observerComponent = Cast<URelativeVelocityObserverComponent>(component);

				FVector referenceLocation = this->GetOwner()->GetActorLocation();
				FVector observerLocation = currentActorObserver->GetActorLocation();

				float distance = FVector::Distance(referenceLocation, observerLocation);

				float dealocatedDistance = FVector::Distance(originalObserverLocation, currentActorObserver->GetActorLocation());

				observerComponent->OnUpdateDistanceToRferenceUpdate(distance, dealocatedDistance, DeltaTime);
			}
		}
		

	}
	
	for (AActor* currentObserverToRemove : toRemove) 
	{
		this->Observers.Remove(currentObserverToRemove);
	}
}

