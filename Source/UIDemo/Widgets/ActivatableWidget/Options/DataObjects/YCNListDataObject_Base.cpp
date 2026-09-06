// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Base.h"

void UYCNListDataObject_Base::OnDataObjectInitialized()
{

}

void UYCNListDataObject_Base::NotifyListDataModified(UYCNListDataObject_Base* InModifiedData, EOptionsListDataModifyReason InModifyReason)
{
	OnListDataModified.Broadcast(InModifiedData, InModifyReason);
}

void UYCNListDataObject_Base::InitDataObject()
{
	OnDataObjectInitialized();
}
