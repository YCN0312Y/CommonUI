// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "YCNLoadingScreenSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "YCN Loading Screen Settings"))
class UIDEMO_API UYCNLoadingScreenSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	TSoftClassPtr<UUserWidget>LoadingScreenWidgetClass;

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	float HoldLoadingScreenExtraSeconds = 3.f;

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	bool bShouldLoadingScreenInEditor = false;

public:
	TSubclassOf<UUserWidget>GetLoadingScreenWidgetClassChecked()const;
};
