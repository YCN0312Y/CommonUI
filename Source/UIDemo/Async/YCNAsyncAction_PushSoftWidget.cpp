// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Async/YCNAsyncAction_PushSoftWidget.h"
#include "UIDemo/Subsystems/YCNWidgetSubsystem.h"
#include "UIDemo/Widgets/YCNWidget_ActivatableBase.h"

#include "UIDemo/YCNDebugHelper.h"

void UYCNAsyncAction_PushSoftWidget::Activate()
{
	UYCNWidgetSubsystem* WidgetSubsystem = UYCNWidgetSubsystem::Get(CachedOwningWorld.Get());
	WidgetSubsystem->PushSoftWidgetToStackAynsc(CachedWidgetStackTag, CachedSoftWidgetClass,
		[this](EAsyncPushWidgetState InPushState, UYCNWidget_ActivatableBase* PushWidget) {
			switch (InPushState)
			{
			case EAsyncPushWidgetState::CreateWidget:
				//设置拥有者控制器
				PushWidget->SetOwningPlayer(CachedOwningPC.Get());
				OnWidgetCreateBeforePush.Broadcast(PushWidget);

				break;
			case EAsyncPushWidgetState::PushWidget:
				AfterPush.Broadcast(PushWidget);
				if (bCachedFocusOnNewlyPushedWidget)
				{
					if (UWidget* WidgetToFocus = PushWidget->GetDesiredFocusTarget())
					{
						//将获取到的目标控件设置为焦点
						WidgetToFocus->SetFocus();
					}
				}

				SetReadyToDestroy();
				break;
			}
		});
}

UYCNAsyncAction_PushSoftWidget* UYCNAsyncAction_PushSoftWidget::PushSoftWidget(
	const UObject* WorldContextObject, APlayerController* OwningPlayerController, 
	TSoftClassPtr<UYCNWidget_ActivatableBase> InSoftWidgetCLass, 
	UPARAM(meta = (Categories = "YCN.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
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

			Node->CachedOwningWorld = World;
			Node->CachedOwningPC = OwningPlayerController;
			Node->CachedSoftWidgetClass = InSoftWidgetCLass;
			Node->CachedWidgetStackTag = InWidgetStackTag;
			Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;

			Node->RegisterWithGameInstance(World);
			return Node;
		}
	}

	return nullptr;
}
