// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/OnPersuitScreen.h"
#include "Components/TextBlock.h"

void UOnPersuitScreen::SetTotalPoints(float totalPoints)
{
	FString totalPointsStr = FString::Printf(TEXT("%.2f"), totalPoints);
	this->TotalPointsCounter->SetText(FText::FromString(totalPointsStr));
}

void UOnPersuitScreen::NativeConstruct()
{
	Super::NativeConstruct();
}
