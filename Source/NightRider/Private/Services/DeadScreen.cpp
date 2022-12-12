// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/DeadScreen.h"

#include "Components/TextBlock.h"

void UDeadScreen::SetDeadZombiesValue(int value)
{
	FString valueStr = FString::Printf(TEXT("%i"), value);
	this->DeadZombiesValue->SetText(FText::FromString(valueStr));
}

void UDeadScreen::SetTotalDistanceValue(float value)
{
	FString valueStr = FString::Printf(TEXT("%.2f"), value);
	this->TotalDistanceValue->SetText(FText::FromString(valueStr));
}

void UDeadScreen::SetTotalPointsValue(float value)
{
	FString valueStr = FString::Printf(TEXT("%.2f"), value);
	this->TotalPointsValue->SetText(FText::FromString(valueStr));
}
