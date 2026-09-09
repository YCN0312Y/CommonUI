// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_Scalar.h"

void UYCNWidget_ListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UYCNWidget_ListEntry_Scalar::OnOwningListDataObjectSet(UYCNListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);
}

void UYCNWidget_ListEntry_Scalar::OnOwningListDataObjectModified(UYCNListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason InModifyReason)
{

}
