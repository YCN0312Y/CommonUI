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
	//根据标签获取软控件类
	UFUNCTION(BlueprintPure, Category = "YCN Function Library")
	static TSoftClassPtr<UYCNWidget_ActivatableBase> GetSoftWidgetClassByTag(UPARAM(meta = (Categories = "YCN.Widget")) FGameplayTag InWidgetTag);
	//根据标签获取选项详情图片
	UFUNCTION(BlueprintPure, Category = "YCN Function Library")
	static TSoftObjectPtr<UTexture2D>GetOptionsSoftImageByTag(UPARAM(meta = (Categories = "YCN.Image")) FGameplayTag InImageTag);
};
