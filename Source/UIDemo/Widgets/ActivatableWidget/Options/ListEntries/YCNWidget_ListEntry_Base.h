// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UIDemo/YCNEnumType.h"
#include "YCNWidget_ListEntry_Base.generated.h"

class UCommonTextBlock;
class UYCNListDataObject_Base;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	//切换主标签的时候自动调用
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject)override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	//当前条目被分配了一个列表数据对象
	virtual void OnOwningListDataObjectSet(UYCNListDataObject_Base* InOwningListDataObject);
	//当前条目关联的数据被修改
	virtual void OnOwningListDataObjectModified(UYCNListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason InModifyReason);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	TObjectPtr<UCommonTextBlock>CommonText_SettingDisplayName;

protected:
	void SelectThisEntryWidget();
public:
	//蓝图调用选择标签函数
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnListEntryWidgetSelectionChanged(bool bIsSelected);
	//蓝图调用悬停标签函数
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnListEntryWidgetHovered(bool bWasHovered, bool bIsEntryWidgetStillSelected);
	void NativeOnListEntryWidgetHovered(bool bWasHovered);
};
