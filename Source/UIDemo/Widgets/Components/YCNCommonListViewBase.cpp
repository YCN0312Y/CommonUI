// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/Components/YCNCommonListViewBase.h"
#include "UIDemo/DataAssets/YCNDataAsset_DataListEntry.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_Base.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Base.h"
#include "Editor/WidgetCompilerLog.h"

UUserWidget& UYCNCommonListViewBase::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (IsDesignTime())
	{
		//如果处于编辑器状态就返回父类
		return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	}

	UYCNListDataObject_Base* DataObjectItem = Cast<UYCNListDataObject_Base>(Item);
	if (DataObjectItem)
	{
		//根据数据对象类型查找对应的小条目控件
		TSubclassOf<UYCNWidget_ListEntry_Base>FoundWidgetClass = DataListEntryMapping->FindEntryWidgetClassByDataObject(DataObjectItem);
		return GenerateTypedEntry<UYCNWidget_ListEntry_Base>(FoundWidgetClass, OwnerTable);
	}

	return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
}

#if WITH_EDITOR
void UYCNCommonListViewBase::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);
	if (!DataListEntryMapping)
	{
		CompileLog.Error(FText::FromString(TEXT("DataListEntryMapping无效!+")));
	}
}
#endif
