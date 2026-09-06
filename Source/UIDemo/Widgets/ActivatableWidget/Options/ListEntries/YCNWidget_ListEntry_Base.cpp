// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_Base.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Base.h"
#include "CommonTextBlock.h"
#include "Components/ListView.h"

void UYCNWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	SetVisibility(ESlateVisibility::Visible);
	//ListItemObject 来自 遍历在SetListItems中传入的数组，来当数据。
	//然后把每条数据的显示名称设置成这个数据的显示名称
	OnOwningListDataObjectSet(CastChecked<UYCNListDataObject_Base>(ListItemObject));
}

void UYCNWidget_ListEntry_Base::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
	BP_OnListEntryWidgetSelectionChanged(bIsSelected);
}

void UYCNWidget_ListEntry_Base::NativeOnListEntryWidgetHovered(bool bWasHovered)
{
	BP_OnListEntryWidgetHovered(bWasHovered, IsListItemSelected());
}

void UYCNWidget_ListEntry_Base::OnOwningListDataObjectSet(UYCNListDataObject_Base* InOwningListDataObject)
{
	if (CommonText_SettingDisplayName)
	{
		CommonText_SettingDisplayName->SetText(InOwningListDataObject->GetDataDisplayName());
		if (!InOwningListDataObject->OnListDataModified.IsBoundToObject(this))
		{
			InOwningListDataObject->OnListDataModified.AddUObject(this, &UYCNWidget_ListEntry_Base::OnOwningListDataObjectModified);
		}
	}
}

void UYCNWidget_ListEntry_Base::OnOwningListDataObjectModified(UYCNListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason InModifyReason)
{

}

void UYCNWidget_ListEntry_Base::SelectThisEntryWidget()
{
	CastChecked<UListView>(GetOwningListView())->SetSelectedItem(GetListItem());
}
