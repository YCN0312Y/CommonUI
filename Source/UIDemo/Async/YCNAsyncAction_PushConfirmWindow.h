// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UIDemo/YCNEnumType.h"
#include "YCNAsyncAction_PushConfirmWindow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushConfirmWindowDelegate, EConfirmWindowButtonType, ButtonType);

UCLASS()
class UIDEMO_API UYCNAsyncAction_PushConfirmWindow : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate()override;

private:
	//缓存拥有的世界
	TWeakObjectPtr<UWorld>CachedOwningWorld;
	//缓存弹窗类型
	EConfirmWindowType CachedWindowType;
	//缓存弹窗标题
	FText CachedWindowTitle;
	//缓存弹窗消息
	FText CachedWindowMessage;

public:
	UPROPERTY(BlueprintAssignable)
	FOnPushConfirmWindowDelegate OnButtonClicked;

public:
	UFUNCTION(BlueprintCallable, Category = YCNWidget, meta = (WorldContext = "WorldContextObject", HidPin = "WorldContextObject", DisplayName = "Push Conrirmation Window"))
	static UYCNAsyncAction_PushConfirmWindow* PushConfirmWindow(const UObject* WorldContextObject,
		EConfirmWindowType InWindowType,
		FText InWindowTitle,
		FText InWindowMessage);
};
