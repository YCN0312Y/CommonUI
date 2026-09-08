// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Base.h"
#include "YCNListDataObject_Value.generated.h"

class FYCNOptionsDataInteractionHelper;

UCLASS(Abstract)
class UIDEMO_API UYCNListDataObject_Value : public UYCNListDataObject_Base
{
	GENERATED_BODY()
public:
	//是否有值可以重置  当 DafaultStringValue 已经设置了值就为真
	virtual bool HasDefaultValue()const override { return DefaultStringValue.IsSet(); }

protected:
	//数据动态获取智能指针
	TSharedPtr<FYCNOptionsDataInteractionHelper>DataDynamciGetter;
	//数据动态设置智能指针
	TSharedPtr<FYCNOptionsDataInteractionHelper>DataDynamciSetter;

private:
	//默认字符串值
	TOptional<FString>DefaultStringValue;

public:
	void SetDataDynamicGetter(const TSharedPtr<FYCNOptionsDataInteractionHelper>& InDynamciGetter);
	void SetDataDynamicSetter(const TSharedPtr<FYCNOptionsDataInteractionHelper>& InDynamciSetter);

	//设置默认字符串值
	void SetDefaultStringValue(const FString& InDefaultValue) { DefaultStringValue = InDefaultValue; }
	//获取默认字符串值
	FString GetDefaultStringValue()const { return DefaultStringValue.GetValue(); }
};
