// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_String.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_String.h"
#include "UIDemo/Widgets/Components/YCNCommonButtonBase.h"
#include "UIDemo/Widgets/Components/YCNCommonRotatorBase.h"

void UYCNWidget_ListEntry_String::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (CommonButton_Last)
	{
		CommonButton_Last->OnClicked().AddUObject(this, &UYCNWidget_ListEntry_String::OnClickedCommonButton_Last);
	}
	if (CommonButton_Next)
	{
		CommonButton_Next->OnClicked().AddUObject(this, &UYCNWidget_ListEntry_String::OnClickedCommonButton_Next);
	}
	if (CommonRotator_AvailableOptions)
	{
		CommonRotator_AvailableOptions->OnClicked().AddLambda(
			[this]()
			{
				SelectThisEntryWidget();
			});
	}
}

void UYCNWidget_ListEntry_String::OnOwningListDataObjectSet(UYCNListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningStringDataObject = CastChecked<UYCNListDataObject_String>(InOwningListDataObject);

	//填充当前标签的所有选项
	CommonRotator_AvailableOptions->PopulateTextLabels(CachedOwningStringDataObject->GetAvailableOptionTextArray());
	//设置当前选择的选项
	CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentTextValue());
}

void UYCNWidget_ListEntry_String::OnOwningListDataObjectModified(UYCNListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason InModifyReason)
{
	if (CachedOwningStringDataObject)
	{
		CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentTextValue());
	}
}

void UYCNWidget_ListEntry_String::OnClickedCommonButton_Last()
{
	if (CachedOwningStringDataObject)
	{
		CachedOwningStringDataObject->BackToLastOption();
	}
	SelectThisEntryWidget();
}

void UYCNWidget_ListEntry_String::OnClickedCommonButton_Next()
{
	if (CachedOwningStringDataObject)
	{
		CachedOwningStringDataObject->AdvanceToNextOption();
	}
	SelectThisEntryWidget();
}

