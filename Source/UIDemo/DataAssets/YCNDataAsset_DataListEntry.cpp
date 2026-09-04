// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/DataAssets/YCNDataAsset_DataListEntry.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Base.h"

TSubclassOf<UYCNWidget_ListEntry_Base> UYCNDataAsset_DataListEntry::FindEntryWidgetClassByDataObject(UYCNListDataObject_Base* InDataObject) const
{
	if (!InDataObject)return TSubclassOf<UYCNWidget_ListEntry_Base>();

	for (UClass* DataObjectClass = InDataObject->GetClass(); DataObjectClass; DataObjectClass = DataObjectClass->GetSuperClass())
	{
		TSubclassOf<UYCNListDataObject_Base>ConvertedDataObjectClass = TSubclassOf<UYCNListDataObject_Base>(DataObjectClass);
		if (ConvertedDataObjectClass)
		{
			if (DataObjectListEntryMap.Contains(ConvertedDataObjectClass))
			{
				return DataObjectListEntryMap.FindRef(ConvertedDataObjectClass);
			}
		}
	}
	return TSubclassOf<UYCNWidget_ListEntry_Base>();
}
