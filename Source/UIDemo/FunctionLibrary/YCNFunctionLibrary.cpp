// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/FunctionLibrary/YCNFunctionLibrary.h"
#include "UIDemo/Settings/YCNDeveloperSettings.h"

TSoftClassPtr<UYCNWidget_ActivatableBase> UYCNFunctionLibrary::GetSoftWidgetClassByTag(UPARAM(meta = (Categories = "YCN.Widget")) FGameplayTag InWidgetTag)
{
	const UYCNDeveloperSettings* Setting = GetDefault<UYCNDeveloperSettings>();
	if (Setting)
	{
		if (Setting->WidgetMap.Contains(InWidgetTag))
		{
			return Setting->WidgetMap.FindRef(InWidgetTag);
		}
	}
	return TSoftClassPtr<UYCNWidget_ActivatableBase>();
}
