// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/WorldTilesObservable.h"

#include "Kismet/KismetSystemLibrary.h"

FVector IWorldTilesObservable::GetReferencePosition()
{
    return FVector();
}

FVector IWorldTilesObservable::GetReferenceVelocity()
{
    return FVector();
}

bool IWorldTilesObservable::IsReference()
{
    return false;
}

FVector* IWorldTilesObservable::GetReferenceOffset()
{
    if (!this->ReferenceOffset) 
    {
        this->ReferenceOffset = new FVector();
    }
    
    return this->ReferenceOffset;
}

void IWorldTilesObservable::ResetOffset()
{
    FVector* referenceOfsset =  this->GetReferenceOffset();
    referenceOfsset->X = 0;
    referenceOfsset->Y = 0;
    referenceOfsset->Z = 0;
    this->ReferenceOffset = referenceOfsset;

   if (!this->Ticker) 
    {   
        this->Ticker = NewObject<UWorldTileObserverTicker>();
    }
    
    //this->Ticker->Reference = this;

    this->Ticker->OnTick().AddLambda([this](float DeltaTime) {

        this->UpdateReferenceOffset(DeltaTime);

        FVector* offset = this->GetReferenceOffset();

        UE_LOG(LogTemp, Log,
            TEXT(" REFERENCE OFFSET UPDATED: %.2f frames: %i offset: %.2f %.2f %.2f")
            , DeltaTime
            , UKismetSystemLibrary::GetFrameCount()
            , offset->X
            , offset->Y
            , offset->Z
        );
    });

   /* this->Ticker->OnTick().AddLambda([this](float DeltaTime) { 
        
        this->UpdateReferenceOffset(DeltaTime); 
        
        FVector* offset = this->GetReferenceOffset();
        
        UE_LOG( LogTemp, Log, 
                TEXT(" REFERENCE OFFSET UPDATED: %.2f frames: %i offset: %.2f %.2f %.2f")
            ,   DeltaTime
            ,   UKismetSystemLibrary::GetFrameCount()
            ,   offset->X
            ,   offset->Y
            ,   offset->Z   
        );
    });*/
}

void IWorldTilesObservable::UpdateReferenceOffset(float DeltaTime)
{
    FVector additional = this->GetReferenceVelocity();
    
    FVector* currentOffset = this->GetReferenceOffset();
    currentOffset->X += ( ( additional.X * -1) * DeltaTime );
    currentOffset->Y += ( ( additional.Y * -1) * DeltaTime );
    currentOffset->Z += ( ( additional.Z * -1) * DeltaTime );
    this->ReferenceOffset = currentOffset;
}

void UWorldTileObserverTicker::Tick(float DeltaTime)
{
   /* if (UKismetSystemLibrary::GetFrameCount() > this->LastFrameUpdated )
    {
        this->OnTick().Broadcast(DeltaTime);
    }*/
}

bool UWorldTileObserverTicker::IsTickable() const
{
    return true;
}

bool UWorldTileObserverTicker::IsTickableWhenPaused() const 
{
    return false;
}

bool UWorldTileObserverTicker::IsTickableInEditor() const
{
    return false;
}

TStatId UWorldTileObserverTicker::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UWorldTileObserverTicker, STATGROUP_Tickables);

    //return UObject::GetStatID();
}
