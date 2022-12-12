// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/LevelProgression.h"

#include <Services/Ranking.h>

ERanking ULevelProgression::GetRanking(int level, float points)
{
	URanking* currentRankingService = Cast<URanking>( this->RankingService->GetDefaultObject() ) ;
	
	float aRanking = currentRankingService->GetARankingThreshold(level);
	float bRanking = currentRankingService->GetBRankingThreshold(level);
	
	if (points < bRanking) 
	{
		return ERanking::C;
	}
	else if (points < aRanking) 
	{
		return ERanking::B;
	}
	
	return ERanking::A;
}