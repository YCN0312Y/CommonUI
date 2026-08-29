// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_ActivatableBase.h"
#include "UIDemo/Gameplay/YCNPlayerController.h"

AYCNPlayerController* UYCNWidget_ActivatableBase::GetCachedOwningPC()
{
    if (!CachedOwningPC.IsValid())
    {
        CachedOwningPC = GetOwningPlayer<AYCNPlayerController>();
    }

    return CachedOwningPC.IsValid() ? CachedOwningPC.Get() : nullptr;
}
