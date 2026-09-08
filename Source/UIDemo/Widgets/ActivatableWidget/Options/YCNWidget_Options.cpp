// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/YCNWidget_Options.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNOptionsDataRegistry.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Collection.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_Base.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/YCNWidget_OptionsDetailsView.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Base.h"
#include "UIDemo/Widgets/Components/YCNCommonListViewBase.h"
#include "UIDemo/Widgets/Components/YCNCommonButtonBase.h"
#include "UIDemo/Widgets/Components/YCNTabListWidgetBase.h"
#include "UIDemo/Subsystems/YCNWidgetSubsystem.h"
#include "UIDemo/Settings/YCNGameUserSettings.h"
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
	if (CommonListView_OptionsList)
	{
		CommonListView_OptionsList->OnEntryWidgetGenerated().AddUObject(this, &UYCNWidget_Options::OnOptionsEntryWidgetGenerated);
		CommonListView_OptionsList->OnItemIsHoveredChanged().AddUObject(this, &UYCNWidget_Options::OnOptionsListHovered);
		CommonListView_OptionsList->OnItemSelectionChanged().AddUObject(this, &UYCNWidget_Options::OnOptionsListSelection);
	}
}

void UYCNWidget_Options::NativeConstruct()
{
	Super::NativeConstruct();

	if (DetailsView_ListEntryInfo)
	{
		if (UYCNListDataObject_Base* SelectedItem = CommonListView_OptionsList->GetSelectedItem<UYCNListDataObject_Base>())
		{
			DetailsView_ListEntryInfo->UpdateDetailsViewInfo(SelectedItem, TryGetEntryWidgetClassName(SelectedItem));
		}
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

void UYCNWidget_Options::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	UYCNGameUserSettings::Get()->ApplySettings(true);
}

void UYCNWidget_Options::OnResetBoundActionTriggered()
{
	if (ResettableDataArray.IsEmpty()|| !TabList_OptionsTabs)return;

	if (UYCNWidgetSubsystem::Get(this))
	{
		UCommonButtonBase* SelectedTabButton = TabList_OptionsTabs->GetTabButtonBaseByID(TabList_OptionsTabs->GetActiveTab());
		if (!SelectedTabButton)return;
		const FString SelectedTabButtonName = CastChecked<UYCNCommonButtonBase>(SelectedTabButton)->GetButtonDisplayText().ToString();
		const FString Message = TEXT("确认要将") + SelectedTabButtonName + TEXT("的所有选项恢复默认吗？");

		UYCNWidgetSubsystem::Get(this)->PushConfirmWindowToModalStackAynsc(
			EConfirmWindowType::YesNo,
			FText::FromString(TEXT("重置")),
			FText::FromString(Message),
			[this](EConfirmWindowButtonType InButtonType)
			{
				if (InButtonType != EConfirmWindowButtonType::Confirm)
				{
					return;
				}
				bIsResettingData = true;
				bool bHasDataFailedToReset = false;
				for (UYCNListDataObject_Base* DataToReset : ResettableDataArray)
				{
					if (!DataToReset)continue;

					if (!DataToReset->TryResetBackToDefaultVaule())
					{
						bHasDataFailedToReset = true;
					}
				}

				if (!bHasDataFailedToReset)
				{
					ResettableDataArray.Empty();
					RemoveActionBinding(ResetActionHandle);
				}
				bIsResettingData = false;
			});
	}
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

FString UYCNWidget_Options::TryGetEntryWidgetClassName(UObject* InOwningListItem)
{
	if (!InOwningListItem || !CommonListView_OptionsList)return FString();

	UUserWidget* FoundEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem(InOwningListItem);
	if (FoundEntryWidget)
	{
		return FoundEntryWidget->GetClass()->GetName();
	}

	return TEXT("无效的控件");
}

void UYCNWidget_Options::OnOptionsTabSelected(FName TabID)
{
	if (!CommonListView_OptionsList || !DetailsView_ListEntryInfo)return;

	// 在替换数据前清除旧选择和自定义高亮，不依赖条目回收事件。
	CommonListView_OptionsList->ClearSelection();
	for (UUserWidget* DisplayedEntry : CommonListView_OptionsList->GetDisplayedEntryWidgets())
	{
		if (UYCNWidget_ListEntry_Base* Entry = Cast<UYCNWidget_ListEntry_Base>(DisplayedEntry))
		{
			Entry->BP_OnListEntryWidgetHovered(false, false);
			Entry->BP_OnListEntryWidgetSelectionChanged(false);
		}
	}
	DetailsView_ListEntryInfo->ClearDetailsViewInfo();
	//找到的已注册的源项
	TArray<UYCNListDataObject_Base*>FoundListSourceItems = GetOwningDataRegistry()->GetListSourceItemBySelectedTabID(TabID);
	
	//将当前选择的主标签的子数据设置给List
	CommonListView_OptionsList->SetListItems(FoundListSourceItems);
	CommonListView_OptionsList->RequestRefresh();//刷新后有新的Row时就会调用 OnGenerateEntryWidgetInternal

	if (CommonListView_OptionsList->GetNumItems() != 0)
	{
		CommonListView_OptionsList->NavigateToIndex(0);//让 ListView 导航/移动到第一个索引的条目。
		CommonListView_OptionsList->SetSelectedIndex(0);//将第一项设置为选中状态
	}

	ResettableDataArray.Empty();
	for (UYCNListDataObject_Base* FoundListSourceItem : FoundListSourceItems)
	{
		if (!FoundListSourceItem)continue;
		
		if (!FoundListSourceItem->OnListDataModified.IsBoundToObject(this))
		{
			FoundListSourceItem->OnListDataModified.AddLambda(
				[this](UYCNListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
				{
					if (!ModifiedData || bIsResettingData)return;

					if (ModifiedData->CanResetBackToDefaultVaule())
					{
						ResettableDataArray.AddUnique(ModifiedData);

						if (!GetActionBindings().Contains(ResetActionHandle))
						{
							AddActionBinding(ResetActionHandle);
						}
					}
					else
					{
						if(ResettableDataArray.Contains(ModifiedData))
						{
							ResettableDataArray.Remove(ModifiedData);
						}
					}

					if (ResettableDataArray.IsEmpty())
					{
						RemoveActionBinding(ResetActionHandle);
					}
				});
		}
		
		if (FoundListSourceItem->CanResetBackToDefaultVaule())
		{
			ResettableDataArray.Add(FoundListSourceItem);
		}
	}

	if (ResettableDataArray.IsEmpty())
	{
		RemoveActionBinding(ResetActionHandle);
	}
	else
	{
		if (!GetActionBindings().Contains(ResetActionHandle))
		{
			AddActionBinding(ResetActionHandle);
		}
	}
}

void UYCNWidget_Options::OnOptionsEntryWidgetGenerated(UUserWidget& InGeneratedItem)
{
	if (!CommonListView_OptionsList || !DetailsView_ListEntryInfo)return;

	//对每个生成或复用的条目同步实际选中状态，包括未选中的条目。
	if (UYCNWidget_ListEntry_Base* Entry = Cast<UYCNWidget_ListEntry_Base>(&InGeneratedItem))
	{
		const bool bIsSelected = Entry->IsListItemSelected();
		Entry->BP_OnListEntryWidgetHovered(false, bIsSelected);
		Entry->BP_OnListEntryWidgetSelectionChanged(bIsSelected);
	}

	//获取当前选择的子控件的数据
	UYCNListDataObject_Base* SelectedItem = CommonListView_OptionsList->GetSelectedItem<UYCNListDataObject_Base>();
	if (!SelectedItem)return;
	
	//只在当前选中项对应的条目生成完成时更新详情
	if (CommonListView_OptionsList->GetEntryWidgetFromItem(SelectedItem) == &InGeneratedItem)
	{
		DetailsView_ListEntryInfo->UpdateDetailsViewInfo(SelectedItem, InGeneratedItem.GetClass()->GetName());
	}
}

void UYCNWidget_Options::OnOptionsListHovered(UObject* InHoveredItem, bool bWasHovered)
{
	if (!InHoveredItem || !CommonListView_OptionsList)return;

	//从当前列表数据中获取悬停的数据
	UYCNWidget_ListEntry_Base* HoveredEntry = CommonListView_OptionsList->GetEntryWidgetFromItem<UYCNWidget_ListEntry_Base>(InHoveredItem);
	if (HoveredEntry)
	{
		HoveredEntry->NativeOnListEntryWidgetHovered(bWasHovered);
	}
}

void UYCNWidget_Options::OnOptionsListSelection(UObject* InSelectionItem)
{
	if (!InSelectionItem || !DetailsView_ListEntryInfo)return;

	UYCNListDataObject_Base* SelectionEntry = Cast<UYCNListDataObject_Base>(InSelectionItem);
	if (SelectionEntry)
	{
		DetailsView_ListEntryInfo->UpdateDetailsViewInfo(SelectionEntry, TryGetEntryWidgetClassName(SelectionEntry));
	}
	
}
