// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Rider.generated.h"


UCLASS()
class NIGHTRIDER_API ARider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARider();

	class URelativeVelocityComponent* RelativeVelocityReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* RiderCamera;
	


	/*
	* -----------------------------------------------------------
	* ON PURSUIT STATE: BEGIN
	* -----------------------------------------------------------
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OnPersuitPosition;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator OnPersuitArmToCameraRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OnPersuitStateArmToCameraRelativePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OnPersuitStateMaxCameraDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OnPersuitStateCameraLens;
	/*
	* -----------------------------------------------------------
	* ON PURSUIT STATE: END
	* -----------------------------------------------------------
	*/

	/*
	* -----------------------------------------------------------
	* ON INTERMEDIARY STATE: START
	* -----------------------------------------------------------
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OnIntermediaryPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator OnIntermediaryStateArmToCameraRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OnIntermediaryStateArmToCameraRelativePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OnIntermediaryStateMaxCameraDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OnIntermediaryCameraLens;
	/*
	* -----------------------------------------------------------
	* ON INTERMEDIARY STATE": END
	* -----------------------------------------------------------
	*/


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* ArmToCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMotorcycle* Motorcycle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScreenTouchRangeToMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScreenTouchRangeToShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ShootTraceRelativeStartPoint;

	void SetMotorcycle(AMotorcycle* motorcycle);
	
	void Move(float x);

	void Shoot();

	UFUNCTION(BlueprintCallable)
	void SetOnPersuitState();

	UFUNCTION(BlueprintCallable)
	void SetIntermediaryState();

	void SetDeadState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class APlayerController* CurrentPlayerController;

	void StartMove(const ETouchIndex::Type fingerIndex, const FVector location);

	void EndMove(const ETouchIndex::Type fingerIndex, const FVector location);

	void ChangeTrail(bool toRight);

	TMap<ETouchIndex::Type, FVector> MovementCursors;

	class ATileSection* AboveTile;

	FVector TargetPosition;

	bool IsMoving;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void OnRiderHit(
		AActor* hittedOtherActor,
		const FHitResult& hit
	);

};
