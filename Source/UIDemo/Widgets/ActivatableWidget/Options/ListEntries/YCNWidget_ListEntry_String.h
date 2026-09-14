// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_Base.h"
#include "YCNWidget_ListEntry_String.generated.h"

class UYCNCommonButtonBase;
class UYCNCommonRotatorBase;
class UYCNListDataObject_String;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNWidget_ListEntry_String : public UYCNWidget_ListEntry_Base
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized()override;
	//当前条目被分配了一个列表数据对象
	virtual void OnOwningListDataObjectSet(UYCNListDataObject_Base* InOwningListDataObject)override;

	//当前条目关联的数据被修改
	virtual void OnOwningListDataObjectModified(UYCNListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason InModifyReason)override;

	//设置数据是否被禁用
	virtual void OnToggleEditableState(bool bIsEditable)override;

private:
	//上一个
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UYCNCommonButtonBase>CommonButton_Last;
	//可选内容
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UYCNCommonRotatorBase>CommonRotator_AvailableOptions;
	//下一个
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UYCNCommonButtonBase>CommonButton_Next;

	//缓存的拥有字符串数据对象
	UPROPERTY(Transient)
	TObjectPtr<UYCNListDataObject_String>CachedOwningStringDataObject;

private:
	void OnClickedCommonButton_Last();
	void OnClickedCommonButton_Next();
};
