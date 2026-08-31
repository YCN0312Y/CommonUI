// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Collection.h"

TArray<UYCNListDataObject_Base*> UYCNListDataObject_Collection::GetAllChildListData() const
{
	return ChildDataList;
}

bool UYCNListDataObject_Collection::HasAnyChildListData() const
{
	//列表不为空就返回真，反之亦然
	return !ChildDataList.IsEmpty();
}

void UYCNListDataObject_Collection::AddDataToChildDataList(UYCNListDataObject_Base* InData)
{
	InData->InitDataObject();
	InData->SetParentData(this);

	ChildDataList.Add(InData);
}
