// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Subsystems/YCNWidgetSubsystem.h"
#include "Engine/AssetManager.h"
#include "UIDemo/Widgets/YCNWidget_MainLayout.h"
#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_ActivatableBase.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_ConfirmWindow.h"
#include "UIDemo/GameplayTags/YCNGameplayTags.h"
#include "UIDemo/FunctionLibrary/YCNFunctionLibrary.h"

#include "UIDemo/YCNDebugHelper.h"

UYCNWidgetSubsystem* UYCNWidgetSubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

		return UGameInstance::GetSubsystem<UYCNWidgetSubsystem>(World->GetGameInstance());
	}
	return nullptr;
}

bool UYCNWidgetSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*>YCNClasss;
		GetDerivedClasses(GetClass(), YCNClasss);
		//当前不是专用服务器且没有派生类的时候才会真
		return YCNClasss.IsEmpty();
	}
	return false;
}

void UYCNWidgetSubsystem::RegisterCreateMainLayoutWidget(UYCNWidget_MainLayout* InCreateMainLayout)
{
	if (!InCreateMainLayout)return;
	
	CreateMainLayout = InCreateMainLayout;
}

void UYCNWidgetSubsystem::PushSoftWidgetToStackAynsc(const FGameplayTag& InWidgetStackTag, 
	TSoftClassPtr<UYCNWidget_ActivatableBase> InSoftWidgetClass, 
	TFunction<void(EAsyncPushWidgetState, UYCNWidget_ActivatableBase*)> AysncPushStateCallback)
{
	if (InSoftWidgetClass.IsNull())return;

	//异步加载
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this, InSoftWidgetClass, InWidgetStackTag, AysncPushStateCallback]()
			{
				UClass* LoadedClass = InSoftWidgetClass.Get();
				if (LoadedClass && CreateMainLayout)
				{
					//根据标签获取到可激活的控件堆栈
					UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreateMainLayout->FindWidgetStackByTag(InWidgetStackTag);
					//再向这个可激活的控件堆栈里面添加已经激活的控件
					UYCNWidget_ActivatableBase * CreateWidget = FoundWidgetStack->AddWidget<UYCNWidget_ActivatableBase>(
						LoadedClass,
						[AysncPushStateCallback](UYCNWidget_ActivatableBase& CreatedWidget)
						{
							//创建LoadedClass控件
							AysncPushStateCallback(EAsyncPushWidgetState::CreateWidget, &CreatedWidget);

						});
					//把刚创建的控件推送到堆栈
					AysncPushStateCallback(EAsyncPushWidgetState::PushWidget, CreateWidget);
				}
			})
	);
}

void UYCNWidgetSubsystem::PushConfirmWindowToModalStackAynsc(
	EConfirmWindowType InWindowType, 
	const FText& InWindowTitle, const FText& InWindowMessage, 
	TFunction<void(EConfirmWindowButtonType)> ButtonClickedCallback)
{
	UYCNConfirmWindowInfoObject* CreatedInfoObject = nullptr;

	switch (InWindowType)
	{
	case EConfirmWindowType::OK:
		CreatedInfoObject = UYCNConfirmWindowInfoObject::CreateOKWindow(InWindowTitle, InWindowMessage);
		break;
	case EConfirmWindowType::YesNo:
		CreatedInfoObject = UYCNConfirmWindowInfoObject::CreateYesNoWindow(InWindowTitle, InWindowMessage);
		break;
	}

	PushSoftWidgetToStackAynsc(
		YCNGameplayTags::YCN_WidgetStack_Modal,
		UYCNFunctionLibrary::GetSoftWidgetClassByTag(YCNGameplayTags::YCN_Widget_Confirm),
		[CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushState, UYCNWidget_ActivatableBase* InPushWidget)
		{
			//将创建的控件转换成确认窗口类型
			UYCNWidget_ConfirmWindow* CreatedConfirmWindow = Cast<UYCNWidget_ConfirmWindow>(InPushWidget);
			if (CreatedConfirmWindow)
			{
				//初始化窗口
				CreatedConfirmWindow->InitConfirmWindow(CreatedInfoObject, ButtonClickedCallback);
			}
		}
	);
}
