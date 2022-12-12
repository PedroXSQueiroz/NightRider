// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Statistcs.h"

#include <NightRider/NightRiderGameMode.h>
#include <Entities/Zombie.h>
#include <Kismet/GameplayStatics.h>


void UStatistcs::Init()
{
	this->OnBarrierPerfectDodge().Clear();
	
	this->BarriersPerfectallyDodged = 0;

	this->OnBarrierPerfectDodge().AddLambda([&]() {
		this->BarriersPerfectallyDodged++;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf( TEXT("Passed through center, counter + %i"), this->BarriersPerfectallyDodged) );
	});

	this->OnZombieKilled().AddLambda([&](AZombie* zombie) {
		
		UClass* zombieType = zombie->GetClass();

		if (this->ZombiesKilledByType.Contains(zombieType)) 
		{
			this->ZombiesKilledByType[zombieType]++;
		}
		else 
		{
			this->ZombiesKilledByType.Add(zombieType, 1);
		}
	});

	this->TotalPoints.Emplace(0);
	this->DistanceRunnned = 0;
	this->BarriersPerfectallyDodged = 0;
	this->ZombiesKilledByType.Empty();

}

float UStatistcs::GetTotalPoints()
{
	float currentTotalPoints = this->DistanceRunnned  + ( this->DistanceRunnned * this->GetTotalMultipliers() );
		
	this->TotalPoints.Emplace(currentTotalPoints);
	
	return this->TotalPoints.GetValue();
}

int UStatistcs::GetTotalZombiesKilled()
{
	int totalZombies = 0;
	
	TArray<TSubclassOf<AZombie>> zombiesKilled;

	this->ZombiesKilledByType.GenerateKeyArray(zombiesKilled);
	
	for (TSubclassOf<AZombie> currentZombieType : zombiesKilled)
	{
		totalZombies += this->ZombiesKilledByType[currentZombieType];
	}
	
	return totalZombies;
}

float UStatistcs::GetTotalMultipliers()
{
	float totalZombiesMultiplier = 0;

	TArray<TSubclassOf<AZombie>> zombiesKilled;

	this->ZombiesKilledByType.GenerateKeyArray(zombiesKilled);

	for (TSubclassOf<AZombie> currentZombieType : zombiesKilled)
	{
		totalZombiesMultiplier += this->ZombieTypeToPoints[currentZombieType] * this->ZombiesKilledByType[currentZombieType];
	}

	return totalZombiesMultiplier;
}

void UStatistcs::PersistRecord()
{
	
	this->RecordDistanceRunnned = 
		this->DistanceRunnned > this->RecordDistanceRunnned ?
			this->DistanceRunnned :
			this->RecordDistanceRunnned;

	int totalZombieKilled = 0;
	
	TArray<TSubclassOf<AZombie>> zombiesKilled;

	this->ZombiesKilledByType.GenerateKeyArray(zombiesKilled);

	for (TSubclassOf<AZombie> currentZombieType : zombiesKilled)
	{
		totalZombieKilled += this->ZombiesKilledByType[currentZombieType];
	}
	
	this->RecordTotalZombiesKilled =
		totalZombieKilled > this->RecordTotalZombiesKilled ?
			totalZombieKilled :
			this->RecordTotalZombiesKilled;


	
	this->RecordBarriersPerfectallyDodged =
		this->BarriersPerfectallyDodged > this->RecordBarriersPerfectallyDodged ?
			this->BarriersPerfectallyDodged :
			this->RecordBarriersPerfectallyDodged;
	

	
	float currentTotalPoints = this->GetTotalPoints();
	this->RecordTotalPoints =
		currentTotalPoints > this->RecordTotalPoints ?
			currentTotalPoints :
			this->RecordTotalPoints;

}

void UStatistcs::RegisterBarrierPerfectallyDodged(UWorld* worldTarget)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	currentGameMode->CurrentStatistics->OnBarrierPerfectDodge().Broadcast();
}

void UStatistcs::RegisterZombieKilled(UWorld* worldTarget, AZombie* zombie)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	currentGameMode->CurrentStatistics->OnZombieKilled().Broadcast(zombie);
}

void UStatistcs::AddTotalDistanceRunned(UWorld* worldTarget, float totalDistranceRunned)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	currentGameMode->CurrentStatistics->DistanceRunnned += totalDistranceRunned;
}

int UStatistcs::GetCurrentPlayerLevel(UWorld* worldTarget)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	return currentGameMode->CurrentStatistics->CurrentLevel;
}

float UStatistcs::GetDistanceRunned(UWorld* worldTarget)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	return currentGameMode->CurrentStatistics->DistanceRunnned;
}

template<typename DodgeCallback>
inline void UStatistcs::RegisterBarrierPerfectallyDodgedCallback(UWorld* worldTarget, DodgeCallback callback)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	currentGameMode->CurrentStatistics->OnBarrierPerfectDodge().AddLambda(callback);
}

template<typename ZombieKilledCallback>
void UStatistcs::RegisterZombieKilledCallback(UWorld* worldTarget, ZombieKilledCallback callback)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	currentGameMode->CurrentStatistics->OnZombieKilled().AddLambda(callback);
}

