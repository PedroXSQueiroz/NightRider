// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Initiable.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UInitiable: public UInterface
{
	GENERATED_BODY()
};

template<typename ParamsValues>
struct FInitParams 
{
public:
	
	FInitParams<ParamsValues>(ParamsValues params):ParamsValues(params)
	{
	}

	ParamsValues GetValues() 
	{
		return this->Params;
	}

private:

	ParamsValues Params;
};

class IInitiable 
{	
	GENERATED_BODY()

public:
	
	template<typename ParamsValues>
	void Init(FInitParams<ParamsValues> param);
};
