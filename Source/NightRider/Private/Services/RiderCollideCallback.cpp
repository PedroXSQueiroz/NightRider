// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/RiderCollideCallback.h"

#include <Entities/Rider.h>

URiderCollideCallback::URiderCollideCallback(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void IRiderCollideCallback::OnRiderCollide(ARider* rider)
{
	rider->Die();
}
