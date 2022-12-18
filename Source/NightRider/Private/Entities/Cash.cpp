// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Cash.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include <Services/Statistcs.h>

// Sets default values
ACash::ACash()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("CASH_COLLISION"));
	this->Collision->SetBoxExtent(FVector(5, 5, 10));
	this->Collision->SetRelativeLocation(FVector(0, 0, 5));
	this->Collision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	this->Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	this->Collision->SetNotifyRigidBodyCollision(true);
	this->Collision->SetSimulatePhysics(false);
	this->Collision->SetEnableGravity(false);
	this->Collision->SetupAttachment(this->RootComponent);

	this->CashMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CASH_MESH"));
	this->CashMesh->SetupAttachment(this->Collision);

}

// Called when the game starts or when spawned
void ACash::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACash::OnRiderCollide(ARider* rider)
{
	UStatistcs::AddCash(this->GetWorld(), this->GetAmmount());
	this->Destroy();
}

