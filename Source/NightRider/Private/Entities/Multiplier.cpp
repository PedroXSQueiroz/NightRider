// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Multiplier.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include<Services/Statistcs.h>


// Sets default values
AMultiplier::AMultiplier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->MultiplierCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("MULTIPLIER_COLLISION"));
	this->MultiplierCollision->SetBoxExtent(FVector(5, 5, 10));
	this->MultiplierCollision->SetRelativeLocation(FVector(0, 0, 5));
	this->MultiplierCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	this->MultiplierCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	this->MultiplierCollision->SetNotifyRigidBodyCollision(true);
	this->MultiplierCollision->SetSimulatePhysics(false);
	this->MultiplierCollision->SetEnableGravity(false);
	this->MultiplierCollision->SetupAttachment(this->RootComponent);

	this->MultiplierMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MULTIPLIER_MESH"));
	this->MultiplierMesh->SetupAttachment(this->MultiplierCollision);

}

void AMultiplier::OnRiderCollide(ARider* rider)
{
	this->MultiplierCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	
	UStatistcs::AddMultiplier( this->GetWorld(), this->GetValue() );
	
	this->Destroy(); 
}

// Called every frame
void AMultiplier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

