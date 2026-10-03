// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Settings/YCNLoadingScreenSettings.h"
#include "Blueprint/UserWidget.h"

TSubclassOf<UUserWidget> UYCNLoadingScreenSettings::GetLoadingScreenWidgetClassChecked() const
{
    if (LoadingScreenWidgetClass.IsNull())return TSubclassOf<UUserWidget>();
    TSubclassOf<UUserWidget>LoadedWidget = LoadingScreenWidgetClass.LoadSynchronous();

    return LoadedWidget;
}
