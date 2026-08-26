// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "YCNWidget_MainLayout.generated.h"

class UCommonActivatableWidgetContainerBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNWidget_MainLayout : public UCommonUserWidget
{
	GENERATED_BODY()
	
private:
	//注册控件堆栈映射表
	UPROPERTY(Transient)
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*>RegisteredWidgetStackMap;

protected:
	//注册控件到堆栈
	UFUNCTION(BlueprintCallable, Category = YCNWidget)
	void RegisteredWidgetStack(UPARAM(meta = (Categories = "YCN.WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* WidgetStack);

public:
	//根据标签查找控件堆栈
	UCommonActivatableWidgetContainerBase* FindWidgetStackByTag(const FGameplayTag& InTag)const;

};
