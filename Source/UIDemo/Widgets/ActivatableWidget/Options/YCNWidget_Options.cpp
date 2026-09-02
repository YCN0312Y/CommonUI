// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/YCNWidget_Options.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNOptionsDataRegistry.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Collection.h"
#include "UIDemo/Widgets/Components/YCNTabListWidgetBase.h"
#include "Input/CommonUIInputTypes.h"
#include "ICommonInputModule.h"
#include "UIDemo/YCNDebugHelper.h"

void UYCNWidget_Options::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction, 
				true, 
				FSimpleDelegate::CreateUObject(this, &UYCNWidget_Options::OnResetBoundActionTriggered)));
	}

	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(), 
			true, 
			FSimpleDelegate::CreateUObject(this, &UYCNWidget_Options::OnBackBoundActionTriggered)));

	if (TabList_OptionsTabs)
	{
		TabList_OptionsTabs->OnTabSelected.AddDynamic(this, &UYCNWidget_Options::OnOptionsTabSelected);
	}
}

void UYCNWidget_Options::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (TabList_OptionsTabs)
	{
		for (UYCNListDataObject_Collection* TabCollection : GetOwningDataRegistry()->GetRegistryOptionsTabList())
		{
			if (!TabCollection)continue;

			//如果不为空就继续循环，因为该按钮已存在
			if (TabList_OptionsTabs->GetTabButtonBaseByID(TabCollection->GetDataID()) != nullptr)continue;
			TabList_OptionsTabs->RequestRegisterTab(TabCollection->GetDataID(), TabCollection->GetDataDisplayName());
		}
	}
}

void UYCNWidget_Options::OnResetBoundActionTriggered()
{
	Debug::Print(TEXT("重置"));
}

void UYCNWidget_Options::OnBackBoundActionTriggered()
{
	//返回上一个控件
	DeactivateWidget();
}

UYCNOptionsDataRegistry* UYCNWidget_Options::GetOwningDataRegistry()
{
	if (IsValid(CreateOwningDataRegistry))return CreateOwningDataRegistry;
	
	CreateOwningDataRegistry = NewObject<UYCNOptionsDataRegistry>(this);

	if (IsValid(CreateOwningDataRegistry))
	{
		CreateOwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
	}

	return CreateOwningDataRegistry;
}

void UYCNWidget_Options::OnOptionsTabSelected(FName TabID)
{

}
