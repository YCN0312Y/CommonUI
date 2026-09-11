// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Scalar.h"
#include "UIDemo/Msic/YCNOptionsDataInteractionHelper.h"

float UYCNListDataObject_Scalar::StringToFloat(const FString NewValue)const
{
	float OutFloatValue = 0.f;
	//将获取到的字符传给 OutFloatValue
	LexFromString(OutFloatValue, *NewValue);

	return OutFloatValue;
}

FCommonNumberFormattingOptions UYCNListDataObject_Scalar::NoDecimal()
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = 0;//保留0位小数点
	return Options;
}

FCommonNumberFormattingOptions UYCNListDataObject_Scalar::WithDecimal(int32 NumFracDigit)
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = NumFracDigit;
	return Options;
}

void UYCNListDataObject_Scalar::SetCurrentValue(float InNewValue)
{
	if(DataDynamciSetter)
	{
		/*
		* InNewValue 根据根据 DisplayValueRange 的区间映射到 OutputValueRange 的区间中
		* 如果InNewValue = 0.1 在(0,1)中为0.1，在(0,2)中为0.2
		*/
		const float ClampedValue = FMath::GetMappedRangeValueClamped(DisplayValueRange, OutputValueRange, InNewValue);
		DataDynamciSetter->SetValudFromString(LexToString(ClampedValue));//将值保存到用户设置中

		NotifyListDataModified(this);
	}
}

float UYCNListDataObject_Scalar::GetCurrentValue()const
{
	if (DataDynamciGetter)
	{
		//获取用户设置中的值
		return FMath::GetMappedRangeValueClamped(OutputValueRange, DisplayValueRange, StringToFloat(DataDynamciGetter->GetValudFromString()));
	}
	return 0.0f;
}

bool UYCNListDataObject_Scalar::CanResetBackToDefaultVaule() const
{
	if (HasDefaultValue() && DataDynamciGetter)
	{
		const float DafaultVaule = StringToFloat(GetDefaultStringValue());
		const float CurrentValue = StringToFloat(DataDynamciGetter->GetValudFromString());


		return !FMath::IsNearlyEqual(DafaultVaule, CurrentValue, 0.01f);
	}
	return false;
}

bool UYCNListDataObject_Scalar::TryResetBackToDefaultVaule()
{
	if (CanResetBackToDefaultVaule())
	{
		if (DataDynamciSetter)
		{
			DataDynamciSetter->SetValudFromString(GetDefaultStringValue());

			NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);

			return true;
		}
	}
	return false;
}
