// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Async/YCNAsyncAction_PushSoftWidget.h"
#include "UIDemo/YCNDebugHelper.h"

UYCNAsyncAction_PushSoftWidget* UYCNAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject, APlayerController* PwningPlayerController, TSoftClassPtr<UYCNWidget_ActivatableBase> InSoftWidgetCLass, FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	if (InSoftWidgetCLass.IsNull())
	{
		Debug::Print(TEXT("向堆栈推送软引用时软引用为空"));
		return nullptr;
	}
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		if (World)
		{
			UYCNAsyncAction_PushSoftWidget* Node = NewObject<UYCNAsyncAction_PushSoftWidget>();
			Node->RegisterWithGameInstance(World);
			return Node;
		}
	}

	return nullptr;
}
