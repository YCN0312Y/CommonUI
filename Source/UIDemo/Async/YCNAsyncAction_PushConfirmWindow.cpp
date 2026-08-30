// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Async/YCNAsyncAction_PushConfirmWindow.h"
#include "UIDemo/Subsystems/YCNWidgetSubsystem.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

void UYCNAsyncAction_PushConfirmWindow::Activate()
{
	Super::Activate();

	UYCNWidgetSubsystem::Get(CachedOwningWorld.Get())->PushConfirmWindowToModalStackAynsc(
		CachedWindowType, 
		CachedWindowTitle, 
		CachedWindowMessage,
		[this](EConfirmWindowButtonType InWindowButtonType)
		{
			OnButtonClicked.Broadcast(InWindowButtonType);

			//销毁异步任务
			SetReadyToDestroy();
		});
}

UYCNAsyncAction_PushConfirmWindow* UYCNAsyncAction_PushConfirmWindow::PushConfirmWindow(const UObject* WorldContextObject, EConfirmWindowType InWindowType, FText InWindowTitle, FText InWindowMessage)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		if (World)
		{
			UYCNAsyncAction_PushConfirmWindow* Node = NewObject<UYCNAsyncAction_PushConfirmWindow>(World);
			if (Node)
			{
				Node->CachedOwningWorld = World;
				Node->CachedWindowType = InWindowType;
				Node->CachedWindowTitle = InWindowTitle;
				Node->CachedWindowMessage = InWindowMessage;
				Node->RegisterWithGameInstance(World);
				return Node;
			}
		}
	}
	return nullptr;

}
