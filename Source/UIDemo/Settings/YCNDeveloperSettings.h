// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "YCNDeveloperSettings.generated.h"

class UYCNWidget_ActivatableBase;

UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "YCN Common UI Settings"))
class UIDEMO_API UYCNDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Widget Soft Reference", meta = (ForceInlineRow, Categories = "YCN.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UYCNWidget_ActivatableBase>>WidgetMap;
	
};
