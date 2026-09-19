// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_Base.h"
#include "YCNWidget_ListEntry_KeyRemap.generated.h"

class UYCNCommonButtonBase;
class UYCNListDataObject_KeyRemap;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNWidget_ListEntry_KeyRemap : public UYCNWidget_ListEntry_Base
{
	GENERATED_BODY()
	
protected:
	//当前条目被分配了一个列表数据对象
	virtual void OnOwningListDataObjectSet(UYCNListDataObject_Base* InOwningListDataObject)override;	
	//当前条目关联的数据被修改
	virtual void OnOwningListDataObjectModified(UYCNListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason InModifyReason)override;
private:
	//键位映射
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UYCNCommonButtonBase>CommonButton_RemapKey;
	//重置键位绑定
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UYCNCommonButtonBase>CommonButton_ResetKeyBinding;

	UPROPERTY(Transient)
	TObjectPtr<UYCNListDataObject_KeyRemap>CachedOwningKeyRemapDataObject;
};
