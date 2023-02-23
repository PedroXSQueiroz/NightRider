// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/ObservableContainers/ObservableContainerCurrentPlayer.h"

TScriptInterface<IWorldTilesObservable> UObservableContainerCurrentPlayer::GetReference(UWorld* world)
{
	IWorldTilesObservable* reference = Cast<IWorldTilesObservable>(world->GetFirstPlayerController()->GetPawn());
	
	TScriptInterface<IWorldTilesObservable> referenceWrapper;

	referenceWrapper.SetObject( Cast<UObject> (reference ) );

	return referenceWrapper;
}
