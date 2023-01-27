// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Record.h"

FRecord::FRecord() 
{
	this->DistanceRunnned = 0;
	this->TotalZombiesKilled = 0;
	this->TotalPoints = 0;
}

FRecord::FRecord(
		float distanceRunned
	,	float totalZombiesKilled
	,	float totalPoints
) 
{
	this->DistanceRunnned = distanceRunned;
	this->TotalZombiesKilled = totalZombiesKilled;
	this->TotalPoints = totalPoints;
}