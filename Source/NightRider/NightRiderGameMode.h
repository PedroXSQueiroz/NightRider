// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"

#include <WorldBuilderModule/Public/Services/WorldTilesObservableContainer.h>

#include "NightRiderGameMode.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ANightRiderGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANightRiderGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWorldBuilder> WorldBuilderType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> InitialScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> OnPersuitScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> DeadScreen;
	
	class UWorldBuilder* CurrentWorldBuilder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMotorcycle>  DefaultMotorcycleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UStatistcs> CurrentStatisticsType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ULevelProgression> LevelProgression;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ShowOnPersuitScreen();

	void ShowDeadScreen();

	UFUNCTION(BlueprintCallable)
	void Restart();

	class UStatistcs* CurrentStatistics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWorldTileFactory> WorldFileFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InitialTilesCount;

private:

	class UUserWidget* CurrentWidgetOnScreen;

protected:

	virtual void Tick(float deltTime) override;

};



