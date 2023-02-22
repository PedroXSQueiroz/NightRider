// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Rider.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include <Entities/RoadTileSection.h>
#include <Entities/Obstacle.h>
#include <Entities/Motorcycle.h>
#include <Entities/Zombie.h>
#include <Services/RelativeVelocityComponent.h>
#include <Services/Statistcs.h>
#include "../NightRiderGameMode.h"

// Sets default values
ARider::ARider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->RelativeVelocityReference = CreateDefaultSubobject<URelativeVelocityComponent>(TEXT("RIDER_VELOCITY_RELATIVE_REFERENCE"));
	
	this->Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("RIDER_ROOT"));
	this->Collision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	this->Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	this->Collision->SetBoxExtent(FVector(5, 10, 5));
	this->Collision->SetSimulatePhysics(true);
	this->Collision->SetNotifyRigidBodyCollision(true);
	this->RootComponent = this->Collision;

	this->ArmToCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("ARM_CAMERA"));
	this->ArmToCamera->SetupAttachment(this->RootComponent);
	
	this->RiderCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	this->RiderCamera->SetupAttachment(this->ArmToCamera, USpringArmComponent::SocketName);

	this->MovementCursors = TMap<ETouchIndex::Type, FVector>();
}

// Called when the game starts or when spawned
void ARider::BeginPlay()
{
	Super::BeginPlay();	
	
	this->RootComponent->SetWorldLocation(this->OnPersuitPosition);
	this->RootComponent->SetWorldRotation(FRotator(0, 0, 0));

	this->RiderCamera->SetActive(true);

	this->TargetPosition = FVector(0, 0, 0);
	this->Collision->BodyInstance.bLockRotation = true;
	this->Collision->BodyInstance.bLockXTranslation = true;
	this->Collision->BodyInstance.bLockZTranslation = true;
	this->Collision->BodyInstance.SetDOFLock(EDOFMode::SixDOF);

	this->SetIntermediaryState();

	this->ResetOffset();
}

void ARider::StartMove(const ETouchIndex::Type fingerIndex, const FVector location)
{
	if (this->MovementCursors.Contains(fingerIndex))
	{
		this->MovementCursors[fingerIndex]= location;
	}
	else
	{
		this->MovementCursors.Add(fingerIndex, location );
	}
}

void ARider::SetMotorcycle(AMotorcycle* motorcycle) 
{
	motorcycle->AddActorWorldOffset(
		FVector(0, 0, 2)
	);
	
	motorcycle->MotorcycleMesh->SetRelativeTransform(
		FTransform(
			FRotator(0, -90, 0),
			FVector(0, 0, 0),
			FVector(0.1, 0.1, 0.1)
		)
	);
	
	this->Motorcycle = motorcycle;
	this->Motorcycle->AttachToActor(
		this
		, FAttachmentTransformRules(
			EAttachmentRule::KeepRelative,
			EAttachmentRule::KeepRelative,
			EAttachmentRule::KeepRelative,
			false
		)
	);
}

void ARider::EndMove(const ETouchIndex::Type fingerIndex, const FVector finalTouchLocation)
{
	if (this->MovementCursors.Contains(fingerIndex)) 
	{
		FVector initialTouchLocation = this->MovementCursors[fingerIndex];
		float touchDistance = FVector::Distance(initialTouchLocation, finalTouchLocation);

		FVector2D viewPortSize = FVector2D();
		GetWorld()->GetGameViewport()->GetViewportSize(viewPortSize);
		
		float minXRange = (viewPortSize.X * this->ScreenTouchRangeToMove) / 100.f;

		if (touchDistance > minXRange) 
		{
			bool goingRight = finalTouchLocation.X > initialTouchLocation.X;
			
			this->ChangeTrail(goingRight);
		}
		
		float minYRange = (viewPortSize.Y * this->ScreenTouchRangeToShoot) / 100.f;

		if (touchDistance > minYRange)
		{
			bool goingRight = finalTouchLocation.Y > initialTouchLocation.Y;

			this->Shoot();
		}

		this->MovementCursors.Remove(fingerIndex);
	}

}


void ARider::ChangeTrail(bool goingRight)
{
	FVector riderLocation = this->GetActorLocation();

	TArray<AActor*> CurrentRoadTiles = TArray<AActor*>();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoadTileSection::StaticClass(), CurrentRoadTiles);

	for (AActor* currentRoadTileActor : CurrentRoadTiles)
	{
		ARoadTileSection* currentRoadTile = Cast<ARoadTileSection>(currentRoadTileActor);

		if (currentRoadTile->IsInArea(riderLocation))
		{

			int trailIndex = currentRoadTile->GetTrailIndexIsIn(riderLocation);

			if (trailIndex != -1)
			{
				int destinyTrail = goingRight ? trailIndex + 1 : trailIndex - 1;

				FVector trailPosition = currentRoadTile->GetTrailMedianPosition(destinyTrail);

				this->TargetPosition = FVector(
					riderLocation.X,
					trailPosition.Y,
					0
				);

			}
		}

	}
}

void ARider::Move(float x)
{
	if (x != 0 && !this->IsMoving) 
	{
		this->IsMoving = true;
		
		this->ChangeTrail(x > 0);
	}

	this->IsMoving = false;
}

void ARider::Shoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Shoot detected"));

	FHitResult shootHit;

	FVector shootStart = this->GetActorLocation() + this->ShootTraceRelativeStartPoint;
	FVector shootEnd = shootStart + ( this->GetActorForwardVector() * 100 );
	
	this->GetWorld()->LineTraceSingleByChannel(shootHit, shootStart, shootEnd, ECollisionChannel::ECC_MAX);


	AActor* hittedActor = shootHit.GetActor();
	
	DrawDebugLine(
		this->GetWorld()
		,shootStart
		,shootHit.TraceEnd
		,FColor::Red
		,true
		,1000000
		,1
		,0.25
	);

	if (hittedActor) 
	{
		if (hittedActor->IsA(AZombie::StaticClass())) 
		{
			AZombie* hittedZombie = Cast<AZombie>(hittedActor);
			
			if (!hittedZombie->GetIsDead()) 
			{
				hittedZombie->OnShooted();
			}
		}
	}
}

void ARider::SetOnPersuitState()
{
	this->ArmToCamera->SetRelativeRotation(this->OnPersuitArmToCameraRotation);
	this->ArmToCamera->TargetArmLength = this->OnPersuitStateMaxCameraDistance;
	this->ArmToCamera->SetRelativeLocation(this->OnPersuitStateArmToCameraRelativePosition);
	this->RiderCamera->FieldOfView = this->OnPersuitStateCameraLens;
	
}

void ARider::SetIntermediaryState()
{
	this->ArmToCamera->SetRelativeRotation(this->OnIntermediaryStateArmToCameraRotation);
	this->ArmToCamera->TargetArmLength = this->OnIntermediaryStateMaxCameraDistance;
	this->ArmToCamera->SetRelativeLocation(this->OnIntermediaryStateArmToCameraRelativePosition);
	this->RiderCamera->FieldOfView = this->OnIntermediaryCameraLens;
}

void ARider::Die()
{
	this->CurrentVelocity = 0;
	this->Collision->SetSimulatePhysics(false);
	
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(this->GetWorld()));

	UStatistcs::SaveRecord(this->GetWorld());

	currentGameMode->ShowDeadScreen();
}

FVector ARider::GetReferencePosition()
{
	return this->GetActorLocation();
}

FVector ARider::GetReferenceVelocity()
{
	return FVector(50, 0, 0);
}

bool ARider::IsReference()
{
	return true;
}

// Called every frame
void ARider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->RelativeVelocityReference->SetVelocity(FVector(this->CurrentVelocity * DeltaTime, 0, 0));

	float newCurrentLocation = FMath::Lerp(this->GetActorLocation().Y, this->TargetPosition.Y, 0.1);
	this->RootComponent->SetWorldLocation( FVector(0, newCurrentLocation, 0) );

	UStatistcs::AddTotalDistanceRunned(this->GetWorld(), ( this->CurrentVelocity * DeltaTime ) / 100 );

	this->UpdateReferenceOffset(DeltaTime);
}

// Called to bind functionality to input
void ARider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ARider::StartMove);
	PlayerInputComponent->BindTouch(IE_Released, this, &ARider::EndMove);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ARider::Shoot);

	PlayerInputComponent->BindAxis("Move Right / Left", this, &ARider::Move);
}

void ARider::OnRiderHit(
		AActor* hittedOtherActor
	,	const FHitResult& hit)
{
	
	if (hittedOtherActor->GetClass()->ImplementsInterface(URiderCollideCallback::StaticClass())) 
	{
		Cast<IRiderCollideCallback>(hittedOtherActor)->OnRiderCollide(this);
	}
}

void ARider::OnRiderOverlap(AActor* hittedOtherActor)
{
	if (hittedOtherActor->GetClass()->ImplementsInterface(URiderCollideCallback::StaticClass()))
	{
		Cast<IRiderCollideCallback>(hittedOtherActor)->OnRiderCollide(this);
	}
}


