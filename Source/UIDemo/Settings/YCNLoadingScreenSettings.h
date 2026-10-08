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
	//在加载完成之后，额外让 Loading Screen 保持显示多少秒
	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	float HoldLoadingScreenExtraSeconds = 3.f;
	//在编辑器中是否应该显示 Loading Screen
	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	bool bShouldLoadingScreenInEditor = false;

public:
	TSubclassOf<UUserWidget>GetLoadingScreenWidgetClassChecked()const;
};
