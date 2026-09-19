// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_KeyRemap.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_KeyRemap.h"
#include "UIDemo/Widgets/Components/YCNCommonButtonBase.h"

void UYCNWidget_ListEntry_KeyRemap::OnOwningListDataObjectSet(UYCNListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningKeyRemapDataObject = CastChecked<UYCNListDataObject_KeyRemap>(InOwningListDataObject);
	CommonButton_RemapKey->SetButtonImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
}

void UYCNWidget_ListEntry_KeyRemap::OnOwningListDataObjectModified(UYCNListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason InModifyReason)
{
	if (!CachedOwningKeyRemapDataObject)return;
	CommonButton_RemapKey->SetButtonImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
}
