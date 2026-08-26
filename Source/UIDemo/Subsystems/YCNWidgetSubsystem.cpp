// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Subsystems/YCNWidgetSubsystem.h"
#include "Engine/AssetManager.h"
#include "UIDemo/Widgets/YCNWidget_MainLayout.h"
#include "UIDemo/Widgets/YCNWidget_ActivatableBase.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

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
	Debug::Print(TEXT("CreateMainLayout已保存"));
}

void UYCNWidgetSubsystem::PushSoftWidgetToStackAynsc(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UYCNWidget_ActivatableBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, UYCNWidget_ActivatableBase*)> AysncPushStateCallback)
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
					UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreateMainLayout->FindWidgetStackByTag(InWidgetStackTag);
					UYCNWidget_ActivatableBase * CreateWidget = FoundWidgetStack->AddWidget<UYCNWidget_ActivatableBase>(
						LoadedClass,
						[AysncPushStateCallback](UYCNWidget_ActivatableBase& CreatedWidget)
						{
							AysncPushStateCallback(EAsyncPushWidgetState::OnCreateBeforePush, &CreatedWidget);

						});
					AysncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreateWidget);
				}
			})
	);
}
