// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/OnPersuitScreen.h"
#include "Components/TextBlock.h"

#include <Services/Statistcs.h>

void UOnPersuitScreen::SetTotalPoints(float totalPoints)
{
	FString totalPointsStr = FString::Printf(TEXT("%.2f"), totalPoints);
	this->TotalPointsCounter->SetText(FText::FromString(totalPointsStr));
}

void UOnPersuitScreen::Init(UWorld* world)
{
	this->CurrentCash = 0;
	this->MultiplierCounter = 0;

	this->WorldReference = world;
	
	if (!this->IsInitiated) 
	{
		this->OnCashEarnedHandle = UStatistcs::RegisterCashEarningCallback(world, [&](int cash) {
			this->CurrentCash += cash;

			FString totalCashStr = FString::Printf(TEXT("%i"), this->CurrentCash);

			this->TotalCashCounter->SetText(FText::FromString(totalCashStr));			

		});

		this->OnMultiplierAaddesHandle = UStatistcs::RegisterMultiplierAddingCallback(world, [&](float multiplier) {
			this->CurrentMultipliers += multiplier;

			FString totalMultiplierStr = FString::Printf(TEXT("%.2f"), this->CurrentMultipliers);
			
			this->MultiplierCounter->SetText(FText::FromString(totalMultiplierStr));
			
		});

		this->IsInitiated = true;
	}
	
}

void UOnPersuitScreen::NativeConstruct()
{
	Super::NativeConstruct();

	this->MultiplierCounter = Cast<UTextBlock>( this->GetWidgetFromName(FName("MultiplierCounter")) );
	this->TotalCashCounter = Cast<UTextBlock>(this->GetWidgetFromName(FName("TotalCashCounter")));
	this->TotalPointsCounter = Cast<UTextBlock>(this->GetWidgetFromName(FName("TotalPointsCounter")));
}

void UOnPersuitScreen::NativeDestruct() 
{
	Super::NativeDestruct();

	UStatistcs::RemoveCashEarningCallback(this->WorldReference, this->OnCashEarnedHandle);
	UStatistcs::RemoveMultiplierAddingCallback(this->WorldReference, this->OnMultiplierAaddesHandle);
}
