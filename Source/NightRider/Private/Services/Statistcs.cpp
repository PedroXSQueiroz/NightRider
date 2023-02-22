// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Statistcs.h"

//#include <NightRider/NightRiderGameMode.h>
#include <Entities/Zombie.h>
#include <Entities/Record.h>

#include "../NightRiderGameMode.h"

#include "UObject/UObjectGlobals.h"

#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h" 

//#include <Kismet/GameplayStatics.h>


void UStatistcs::Init()
{
	this->OnBarrierPerfectDodge().Clear();
	
	this->BarriersPerfectallyDodged = 0;

	this->OnBarrierPerfectDodge().Clear();

	this->OnBarrierPerfectDodge().AddLambda([&]() {
		this->BarriersPerfectallyDodged++;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf( TEXT("Passed through center, counter + %i"), this->BarriersPerfectallyDodged) );
	});

	this->OnZombieKilled().Clear();

	this->OnZombieKilled().AddLambda([&](AZombie* zombie) {
		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Zombie killed"));
		
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

	this->OnCashEarned().Clear();

	this->OnCashEarned().AddLambda([&](int cash) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Cash earned"));
		
		this->CurrentEarnedCash += cash;
	});

	this->OnMultiplierAdded().Clear();

	this->OnMultiplierAdded().AddLambda([&](float multi) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Muliplier increased"));
		
		this->TotalCacthedMultiplier += multi;
	});

	this->TotalPoints.Emplace(0);
	this->DistanceRunnned = 0;
	this->TotalMulipliers = 1;
	this->BarriersPerfectallyDodged = 0;
	this->CurrentEarnedCash = 0;
	this->ZombiesKilledByType.Empty();

	this->RecordTotalPoints = 0;
	this->RecordTotalZombiesKilled = 0;
	this->RecordDistanceRunnned = 0;

}

float UStatistcs::GetTotalPoints()
{
	float currentTotalPoints = ( 
									this->DistanceRunnned 
								+	this->GetTotalZombiePoints()
								) * this->TotalMulipliers;
		
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

float UStatistcs::GetTotalZombiePoints()
{
	float totalPoints = 0;

	TArray<TSubclassOf<AZombie>> zombiesKilled;

	this->ZombiesKilledByType.GenerateKeyArray(zombiesKilled);

	for (TSubclassOf<AZombie> currentZombieType : zombiesKilled)
	{
		totalPoints += this->ZombieTypeToPoints[currentZombieType] * this->ZombiesKilledByType[currentZombieType];
	}

	return totalPoints;
}

float UStatistcs::GetRecordTotalPoints(UWorld* worldTarget)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	return currentGameMode->CurrentStatistics->RecordTotalPoints;
}

int UStatistcs::GetRecordTotalZombiesKilled(UWorld* worldTarget)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	return currentGameMode->CurrentStatistics->RecordTotalZombiesKilled;
}

float UStatistcs::GetRecordDistanceRunned(UWorld* worldTarget)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	return currentGameMode->CurrentStatistics->RecordDistanceRunnned;
}

void UStatistcs::UpdateRecord()
{
	
	FString file = FPaths::ProjectContentDir();
	file.Append(TEXT("Record.json"));

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (FileManager.FileExists(*file))
	{
		FString recordSource = FString();
		
		if (FFileHelper::LoadFileToString(recordSource, *file))
		{
			FRecord* previousRecord = new FRecord();
			
			FJsonObjectConverter::JsonObjectStringToUStruct( recordSource, previousRecord);

			this->RecordTotalPoints = previousRecord->TotalPoints;
			this->RecordDistanceRunnned = previousRecord->DistanceRunnned;
			this->RecordTotalZombiesKilled = previousRecord->TotalZombiesKilled;
		}

		FileManager.DeleteFile(*file);
	}

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

	FRecord currentRecord = FRecord(
								this->RecordDistanceRunnned
							,	this->RecordTotalZombiesKilled
							,	this->RecordTotalPoints);

	FString currentRecordJsonContent;

	FJsonObjectConverter::UStructToJsonObjectString(currentRecord, currentRecordJsonContent);

	FFileHelper::SaveStringToFile(
						currentRecordJsonContent
					,	*file
					,	FFileHelper::EEncodingOptions::AutoDetect
					,	&IFileManager::Get()
					,	FILEWRITE_Append);
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

void UStatistcs::AddMultiplier(UWorld* worldTarget, float multi)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	currentGameMode->CurrentStatistics->OnMultiplierAdded().Broadcast(multi);
}

int UStatistcs::GetCurrentPlayerLevel(UWorld* worldTarget)
{
	ANightRiderGameMode* nightRiderGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	return nightRiderGameMode->CurrentStatistics->CurrentLevel;
}

float UStatistcs::GetDistanceRunned(UWorld* worldTarget)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	return currentGameMode->CurrentStatistics->DistanceRunnned;
}

void UStatistcs::AddCash(UWorld* worldTarget, int cash)
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	currentGameMode->CurrentStatistics->OnCashEarned().Broadcast(cash);
}

void UStatistcs::SaveRecord(UWorld* worldTarget) 
{
	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
	currentGameMode->CurrentStatistics->UpdateRecord();
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

//template<typename MultiplierAddedCallback>
//void UStatistcs::RegisterMultiplierAddingCallback(UWorld* worldTarget, MultiplierAddedCallback callback)
//{
//	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
//	currentGameMode->CurrentStatistics->OnMultiplierAdded().AddLambda(callback);
//}

//template<typename CashEarnedCallback>
//void UStatistcs::RegisterCashEarningCallback(UWorld* worldTarget, CashEarnedCallback callback)
//{
//	ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
//	currentGameMode->CurrentStatistics->OnCashEarned().AddLambda(callback);
//}

