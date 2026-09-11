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

protected:
	//可重置为默认值
	virtual bool CanResetBackToDefaultVaule()const override;
	//尝试重置为默认值
	virtual bool TryResetBackToDefaultVaule()override;
	
private:
	//显示值范围
	TRange<float>DisplayValueRange = TRange<float>(0.f, 1.f);
	//输出值范围
	TRange<float>OutputValueRange = TRange<float>(0.f, 1.f);
	//滑块步长
	float SliderStepSize = 0.1f;
	//数字类型
	ECommonNumericType DisplayNumericType = ECommonNumericType::Number;
	//数字格式选项
	FCommonNumberFormattingOptions NumberFormattingOptions;

private:
	//字符串转float
	float StringToFloat(const FString NewValue)const;
public:
	LIST_DATA_ACCESSOR(TRange<float>, DisplayValueRange);
	LIST_DATA_ACCESSOR(TRange<float>, OutputValueRange);
	LIST_DATA_ACCESSOR(float, SliderStepSize);
	LIST_DATA_ACCESSOR(ECommonNumericType, DisplayNumericType);
	LIST_DATA_ACCESSOR(FCommonNumberFormattingOptions, NumberFormattingOptions);

	//无小数
	static FCommonNumberFormattingOptions NoDecimal();
	//带小数点
	static FCommonNumberFormattingOptions WithDecimal(int32 NumFracDigit);

	float GetCurrentValue()const;
	void SetCurrentValue(float InNewValue);
};
