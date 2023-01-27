// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeadScreen.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class NIGHTRIDER_API UDeadScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* DeadZombiesValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TotalDistanceValue;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TotalPointsValue;

	void SetDeadZombiesValue(int value);

	void SetTotalDistanceValue(float value);

	void SetTotalPointsValue(float value);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* RecordDeadZombiesValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* RecordTotalDistanceValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* RecordTotalPointsValue;

	void SetRecordDeadZombiesValue(int value);

	void SetRecordTotalDistanceValue(float value);

	void SetRecordTotalPointsValue(float value);
};
