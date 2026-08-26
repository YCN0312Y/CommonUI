// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "YCNWidgetSubsystem.generated.h"

class UYCNWidget_MainLayout;
class UYCNWidget_ActivatableBase;

struct FGameplayTag;

//异步推送状态
enum class EAsyncPushWidgetState :uint8
{
	//在推送前创建
	OnCreateBeforePush,
	//在推送后创建
	AfterPush
};

UCLASS()
class UIDEMO_API UYCNWidgetSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	static UYCNWidgetSubsystem* Get(const UObject* WorldContextObject);

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

private:
	//创建主布局
	UPROPERTY()
	UYCNWidget_MainLayout* CreateMainLayout;

public:
	//注册创建主布局组件
	UFUNCTION(BlueprintCallable, Category = YCNWidget, meta = (DisplayName = "注册创建主布局组件"))
	void RegisterCreateMainLayoutWidget(UYCNWidget_MainLayout* InCreateMainLayout);
	//异步将软引用控件推入栈中
	void PushSoftWidgetToStackAynsc(
		const FGameplayTag& InWidgetStackTag, 
		TSoftClassPtr<UYCNWidget_ActivatableBase>InSoftWidgetClass,
		TFunction<void(EAsyncPushWidgetState, UYCNWidget_ActivatableBase*)> AysncPushStateCallback);
};
