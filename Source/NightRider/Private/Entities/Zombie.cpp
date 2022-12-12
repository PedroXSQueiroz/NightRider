// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Zombie.h"

#include <Services/Statistcs.h>
#include <Entities/Rider.h>

#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->ZombieCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ZOMBIE_COLLISION"));
	this->ZombieCollision->SetBoxExtent(FVector(5, 5, 10));
	this->ZombieCollision->SetRelativeLocation(FVector(0, 0, 5));
	this->ZombieCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	this->ZombieCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	this->ZombieCollision->SetNotifyRigidBodyCollision(true);
	this->ZombieCollision->SetSimulatePhysics(false);
	this->ZombieCollision->SetEnableGravity(false);
	this->ZombieCollision->SetupAttachment(this->RootComponent);
	//this->RootComponent = this->ZombieCollision;

	this->ZombieBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ZOMBIE_BODY"));
	this->ZombieBody->SetupAttachment(this->ZombieCollision);
}

bool AZombie::GetIsDead()
{
	return this->IsDead;
}

void AZombie::OnShooted()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Zombie shooted"));
	this->IsDead = true;
	this->ZombieCollision->SetSimulatePhysics(false);
	this->ZombieCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	this->ZombieCollision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	UStatistcs::RegisterZombieKilled(this->GetWorld(), this);
}

void AZombie::OnRiderCollide(ARider* rider)
{
	if (!this->IsDead) 
	{
		rider->Die();
	}
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

