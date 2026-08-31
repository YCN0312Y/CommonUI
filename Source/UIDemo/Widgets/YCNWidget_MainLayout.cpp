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
		}
	}
}

UCommonActivatableWidgetContainerBase* UYCNWidget_MainLayout::FindWidgetStackByTag(const FGameplayTag& InTag) const
{
	if (!RegisteredWidgetStackMap.Contains(InTag))return nullptr;
	
	return RegisteredWidgetStackMap.FindRef(InTag);
}
