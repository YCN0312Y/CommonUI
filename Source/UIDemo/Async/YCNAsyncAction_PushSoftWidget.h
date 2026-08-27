// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"
#include "YCNAsyncAction_PushSoftWidget.generated.h"

class UYCNWidget_ActivatableBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UYCNWidget_ActivatableBase*, PushWidget);

UCLASS()
class UIDEMO_API UYCNAsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	//激活
	virtual void Activate()override;

public:
	//推送前创建控件
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreateBeforePush;
	//推送后创建控件
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate AfterPush;

private:
	//缓存拥有的世界
	TWeakObjectPtr<UWorld>CachedOwningWorld;
	//缓存是谁在推送控件
	TWeakObjectPtr<APlayerController>CachedOwningPC;
	//缓存推送的是哪个控件
	TSoftClassPtr<UYCNWidget_ActivatableBase>CachedSoftWidgetClass;
	//缓存把控件推送到对应标签的堆栈
	FGameplayTag CachedWidgetStackTag;
	//是否推送的控件设置为焦点
	bool bCachedFocusOnNewlyPushedWidget = false;
		
public:
	//推送控件
	UFUNCTION(BlueprintCallable, Category = YCNWidget, meta = (WorldContext = "WorldContextObject", HidPin = "WorldContextObject", DisplayName = "Push Soft Widget ToWidget Stack"))
	static UYCNAsyncAction_PushSoftWidget* PushSoftWidget(const UObject* WorldContextObject,
		APlayerController* OwningPlayerController,
		TSoftClassPtr<UYCNWidget_ActivatableBase>InSoftWidgetCLass,
		UPARAM(meta = (Categories = "YCN.WidgetStack")) FGameplayTag InWidgetStackTag,
		bool bFocusOnNewlyPushedWidget = true);
	
};
