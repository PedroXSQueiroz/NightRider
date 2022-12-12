// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Motorcycle.h"

// Sets default values
AMotorcycle::AMotorcycle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->MotorcycleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MOTORCYCLE_MESH"));
	this->MotorcycleMesh->SetupAttachment(this->RootComponent);

}

// Called when the game starts or when spawned
void AMotorcycle::BeginPlay()
{
	Super::BeginPlay();
	
	this->MotorcycleMesh->SetRelativeLocation(this->RelativePosition);
	this->MotorcycleMesh->SetRelativeRotation(this->RelativeRotator);

}

// Called every frame
void AMotorcycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

