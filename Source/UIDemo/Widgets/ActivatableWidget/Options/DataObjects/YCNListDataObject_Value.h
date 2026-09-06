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

protected:
	//数据动态获取智能指针
	TSharedPtr<FYCNOptionsDataInteractionHelper>DataDynamciGetter;
	//数据动态设置智能指针
	TSharedPtr<FYCNOptionsDataInteractionHelper>DataDynamciSetter;

public:
	void SetDataDynamicGetter(const TSharedPtr<FYCNOptionsDataInteractionHelper>& InDynamciGetter);
	void SetDataDynamicSetter(const TSharedPtr<FYCNOptionsDataInteractionHelper>& InDynamciSetter);
};
