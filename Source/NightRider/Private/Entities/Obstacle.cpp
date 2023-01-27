// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Obstacle.h"
#include "Components/BoxComponent.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->ObstacleCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OBSTACLE_COLLISION"));
	this->ObstacleCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	this->ObstacleCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	this->ObstacleCollision->SetBoxExtent(FVector(5, 5, 5));
	this->ObstacleCollision->SetNotifyRigidBodyCollision(true);
	this->ObstacleCollision->SetSimulatePhysics(false);
	this->ObstacleCollision->SetEnableGravity(false);
	this->ObstacleCollision->SetupAttachment(this->RootComponent);
	//this->RootComponent = this->ObstacleCollision;

	//ConstructorHelpers::FObjectFinder<UStaticMesh> obstacleMeshObject ( TEXT( "StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'" ) );
	
	this->ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OBSTACLE_MESH")); 
	this->ObstacleMesh->SetupAttachment(this->ObstacleCollision);
	/*this->ObstacleMesh->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
	this->ObstacleMesh->SetWorldRotation(FRotator(0, 90, 0));
	this->ObstacleMesh->SetupAttachment(this->ObstacleCollision);*/

	//if (obstacleMeshObject.Succeeded()) 
	//{
	//	//this->ObstacleMesh->SetStaticMesh(obstacleMeshObject.Object);
	//}
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

