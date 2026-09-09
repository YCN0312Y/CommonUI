// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Value.h"
#include "CommonNumericTextBlock.h"
#include "YCNListDataObject_Scalar.generated.h"

UCLASS()
class UIDEMO_API UYCNListDataObject_Scalar : public UYCNListDataObject_Value
{
	GENERATED_BODY()
	
private:
	//显示值范围
	TRange<float>DisplayValueRange = TRange<float>(0.f, 1.f);
	//输出值范围
	TRange<float>OutputValueRange = TRange<float>(0.f, 1.f);
	//滑块步长
	float SliderStepSize = 0.1f;
	//显示的数字类型
	ECommonNumericType DisplayNumericType = ECommonNumericType::Number;
	//数字格式化选项
	FCommonNumberFormattingOptions NumberFormattingOptions;

public:
	LIST_DATA_ACCESSOR(TRange<float>, DisplayValueRange);
	LIST_DATA_ACCESSOR(TRange<float>, OutputValueRange);
	LIST_DATA_ACCESSOR(float, SliderStepSize);
	LIST_DATA_ACCESSOR(ECommonNumericType, DisplayNumericType);
	LIST_DATA_ACCESSOR(FCommonNumberFormattingOptions, NumberFormattingOptions);

	static FCommonNumberFormattingOptions NoDecimal();
	static FCommonNumberFormattingOptions WithDecimal(int32 NumFracDigit);
};
