// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "YCNFunctionLibrary.generated.h"

class UYCNWidget_ActivatableBase;

UCLASS()
class UIDEMO_API UYCNFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "YCN Function Library")
	static TSoftClassPtr<UYCNWidget_ActivatableBase> GetSoftWidgetClassByTag(UPARAM(meta = (Categories = "YCN.Widget")) FGameplayTag InWidgetTag);
};
