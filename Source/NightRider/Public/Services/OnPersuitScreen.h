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
	class UTextBlock* TotalPointsCounter;

	void SetTotalPoints(float totalPoints);

protected:

	virtual void NativeConstruct() override;

};
