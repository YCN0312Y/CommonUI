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
	//推送前创建控件
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreateBeforePush;
	//推送后创建控件
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate AfterPush;

public:
	//推送控件
	UFUNCTION(BlueprintCallable, Category = YCNWidget, meta = (WorldContext = "WorldContextObject", HidPin = "WorldContextObject", DisplayName = "Push Soft Widget ToWidget Stack"))
	static UYCNAsyncAction_PushSoftWidget* PushSoftWidget(const UObject* WorldContextObject,
		APlayerController* PwningPlayerController,
		TSoftClassPtr<UYCNWidget_ActivatableBase>InSoftWidgetCLass,
		UPARAM(meta = (Categories = "YCN.WidgetStack")) FGameplayTag InWidgetStackTag,
		bool bFocusOnNewlyPushedWidget = true);
	
};
