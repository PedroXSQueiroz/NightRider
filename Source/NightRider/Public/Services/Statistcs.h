// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Kismet/GameplayStatics.h>

#include <NightRider/NightRiderGameMode.h>


#include "Statistcs.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class NIGHTRIDER_API UStatistcs : public UObject
{
	GENERATED_BODY()

public:

	void Init();

	/*----------------------------------------------------------------
	* FINAL RESULT PARAMS
	----------------------------------------------------------------*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FINAL_RESULT_PARAM")
	float BarrierPerfecttalyDodgedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FINAL_RESULT_PARAM")
	TMap<TSubclassOf<class AZombie>, float> ZombieTypeToPoints;
	
	/*----------------------------------------------------------------
	* CURRENT
	----------------------------------------------------------------*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CURRENT")
	float DistanceRunnned;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CURRENT")
	TMap< TSubclassOf<class AZombie>, int> ZombiesKilledByType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CURRENT")
	int BarriersPerfectallyDodged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CURRENT")
	float TotalCacthedMultiplier;

	class UUserWidget* ShowOn;

	UFUNCTION(BlueprintCallable)
	virtual float GetTotalPoints();

	UFUNCTION(BlueprintCallable)
	virtual int GetTotalZombiesKilled();

	UFUNCTION(BlueprintCallable)
	virtual float GetTotalZombiePoints();

	UFUNCTION(BlueprintCallable)
	virtual void PersistRecord();

	/*----------------------------------------------------------------
	* RECORD
	----------------------------------------------------------------*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RECORD")
	float RecordDistanceRunnned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RECORD")
	int RecordTotalZombiesKilled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RECORD")
	int RecordBarriersPerfectallyDodged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RECORD")
	float RecordTotalPoints;


	DECLARE_MULTICAST_DELEGATE(FOnBarrierPerfectallyDodged)
	FOnBarrierPerfectallyDodged& OnBarrierPerfectDodge() 
	{
		return this->OnBarrierPerfectallyDodgedEvent;
	};
	
	template<typename DodgeCallback>
	static void RegisterBarrierPerfectallyDodgedCallback(UWorld* worldTarget, DodgeCallback callback);

	static void RegisterBarrierPerfectallyDodged(UWorld* worldTarget);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnZombieKilled, class AZombie*)
	FOnZombieKilled& OnZombieKilled()
	{
		return this->OnZombieKilledEvent;
	};

	template<typename ZombieKilledCallback>
	static void RegisterZombieKilledCallback(UWorld* worldTarget, ZombieKilledCallback callback);
	
	static void RegisterZombieKilled(UWorld* worldTarget, class AZombie* zombie);

	static void AddTotalDistanceRunned(UWorld* worldTarget, float totalDistranceRunned);

	DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplierAdded, float multiplier)
	FMultiplierAdded& OnMultiplierAdded()
	{
		return this->OnMultiplerAddedEvent;
	};

	template<typename MultiplierAddedCallback>
	static FDelegateHandle RegisterMultiplierAddingCallback(UWorld* worldTarget, MultiplierAddedCallback callback)
	{
		ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
		return currentGameMode->CurrentStatistics->OnMultiplierAdded().AddLambda(callback);
	}

	static void RemoveMultiplierAddingCallback(UWorld* worldTarget, FDelegateHandle callback)
	{
		ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
		currentGameMode->CurrentStatistics->OnMultiplierAdded().Remove(callback);
	}

	static void AddMultiplier(UWorld* worldTarget, float multi);

	static int GetCurrentPlayerLevel(UWorld* worldTarget);

	static float GetDistanceRunned(UWorld* worldTarget);

	DECLARE_MULTICAST_DELEGATE_OneParam(FCashEarned, int cash)
	FCashEarned& OnCashEarned()
	{
		return this->OnCashEarningEvent;
	};

	template<typename CashEarnedCallback>
	static FDelegateHandle RegisterCashEarningCallback(UWorld* worldTarget, CashEarnedCallback callback)
	{
		ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
		return currentGameMode->CurrentStatistics->OnCashEarned().AddLambda(callback);
	}

	static void RemoveCashEarningCallback(UWorld* worldTarget, FDelegateHandle callback)
	{
		ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
		currentGameMode->CurrentStatistics->OnCashEarned().Remove(callback);
	}

	/*FCashEarned& UStatistcs::GetCashEarnedEvent(UWorld* worldTarget)
	{
		ANightRiderGameMode* currentGameMode = Cast<ANightRiderGameMode>(UGameplayStatics::GetGameMode(worldTarget));
		return currentGameMode->CurrentStatistics->OnCashEarningEvent;
	}*/

	static void AddCash(UWorld* worldTarget,int cash);

protected:

	TOptional<float> TotalPoints;

	float TotalMulipliers;
	
	FOnBarrierPerfectallyDodged OnBarrierPerfectallyDodgedEvent = FOnBarrierPerfectallyDodged();

	FOnZombieKilled OnZombieKilledEvent = FOnZombieKilled();
	
	FCashEarned OnCashEarningEvent = FCashEarned();

	FMultiplierAdded OnMultiplerAddedEvent = FMultiplierAdded();

	int CurrentLevel;

	int CurrentEarnedCash;

	int TotalCash;
};