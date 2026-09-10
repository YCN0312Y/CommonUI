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
	Options.MaximumFractionalDigits = 0;
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
		const float ClampedValue = FMath::GetMappedRangeValueClamped(DisplayValueRange, OutputValueRange, InNewValue);
		DataDynamciSetter->SetValudFromString(LexToString(ClampedValue));

		NotifyListDataModified(this);
	}
}

float UYCNListDataObject_Scalar::GetCurrentValue()const
{
	if (DataDynamciGetter)
	{
		//获取映射范围内的夹紧值
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
