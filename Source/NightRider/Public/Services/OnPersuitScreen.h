// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnPersuitScreen.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTRIDER_API UOnPersuitScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* TotalPointsCounter = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* MultiplierCounter = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TotalCashCounter = nullptr;

	void SetTotalPoints(float totalPoints);

	void Init(UWorld* world);

protected:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	float CurrentMultipliers;

	int CurrentCash;

	bool IsInitiated = false;

	FDelegateHandle OnCashEarnedHandle;

	FDelegateHandle OnMultiplierAaddesHandle;

	UWorld* WorldReference;

};
