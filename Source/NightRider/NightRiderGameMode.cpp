// Copyright Epic Games, Inc. All Rights Reserved.

#include "NightRiderGameMode.h"
#include "NightRiderCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include <Services/WorldBuilder.h>
#include <Services/Statistcs.h>
#include <Services/OnPersuitScreen.h>
#include <Services/LevelProgression.h>
#include <Entities/Rider.h>
#include <Entities/Motorcycle.h>
#include <Services/DeadScreen.h>

ANightRiderGameMode::ANightRiderGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ANightRiderGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* currentWorldInstance = this->GetWorld();
	
	ARider* currentRider = Cast<ARider>(currentWorldInstance->GetFirstPlayerController()->GetPawn());
	
	AMotorcycle* motorcycle = currentWorldInstance->SpawnActor<AMotorcycle>(this->DefaultMotorcycleType,
		FTransform(
			FRotator(0, 0, 0),
			FVector(0, 0, 0),
			FVector(1, 1, 1)
		));
	currentRider->SetMotorcycle(motorcycle);

	UWorldBuilder* worldBuilder = this->WorldBuilderType.GetDefaultObject();
	worldBuilder->init(currentWorldInstance);
	worldBuilder->SetRider(currentRider);
	worldBuilder->SpawnInitialSections();

	this->CurrentWidgetOnScreen = CreateWidget<UUserWidget>(this->GetWorld(), this->InitialScreen);
	this->CurrentWidgetOnScreen->AddToViewport();

	this->CurrentStatistics = this->CurrentStatisticsType.GetDefaultObject();
	this->CurrentStatistics->Init();
}

void ANightRiderGameMode::ShowOnPersuitScreen()
{
	this->CurrentWidgetOnScreen->RemoveFromViewport();

	UOnPersuitScreen* onPersuitScreen = CreateWidget<UOnPersuitScreen>(this->GetWorld(), this->OnPersuitScreen);
	
	onPersuitScreen->Init(this->GetWorld());
	
	this->CurrentWidgetOnScreen = onPersuitScreen;
	this->CurrentWidgetOnScreen->AddToViewport();
}

void ANightRiderGameMode::ShowDeadScreen()
{
	this->CurrentWidgetOnScreen->RemoveFromViewport();

	UDeadScreen* deadScreen = CreateWidget<UDeadScreen>(this->GetWorld(), this->DeadScreen);

	deadScreen->SetTotalDistanceValue(this->CurrentStatistics->DistanceRunnned);
	deadScreen->SetDeadZombiesValue(this->CurrentStatistics->GetTotalZombiesKilled());
	deadScreen->SetTotalPointsValue(this->CurrentStatistics->GetTotalPoints());

	this->CurrentWidgetOnScreen = deadScreen;
	this->CurrentWidgetOnScreen->AddToViewport();
}

void ANightRiderGameMode::Restart()
{
	UGameplayStatics::OpenLevel( this->GetWorld(), TEXT("Maps/Road"));
}

void ANightRiderGameMode::Tick(float deltTime)
{
	if (this->CurrentWidgetOnScreen->IsA(UOnPersuitScreen::StaticClass()))
	{
		UOnPersuitScreen* persuitScreen = Cast<UOnPersuitScreen>(this->CurrentWidgetOnScreen);
		persuitScreen->SetTotalPoints(this->CurrentStatistics->GetTotalPoints());
	}
}


