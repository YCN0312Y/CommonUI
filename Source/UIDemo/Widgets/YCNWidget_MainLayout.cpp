// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/YCNWidget_MainLayout.h"
#include "UIDemo/YCNDebugHelper.h"

void UYCNWidget_MainLayout::RegisteredWidgetStack(UPARAM(meta = (Categories = "YCN.WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* WidgetStack)
{
	if (!IsDesignTime())
	{
		if (!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			RegisteredWidgetStackMap.Add(InStackTag, WidgetStack);
			Debug::Print(FString::Printf(TEXT("%s 该控件控件堆栈已注册"), *InStackTag.ToString()));
		}
	}
}

UCommonActivatableWidgetContainerBase* UYCNWidget_MainLayout::FindWidgetStackByTag(const FGameplayTag& InTag) const
{
	if (!RegisteredWidgetStackMap.Contains(InTag))
	{
		Debug::Print(FString::Printf(TEXT("无法根据 %s 标签查询到控件堆栈"), *InTag.ToString()));
		return nullptr;
	}
	return RegisteredWidgetStackMap.FindRef(InTag);
}
