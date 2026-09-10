// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_Scalar.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Scalar.h"
#include "AnalogSlider.h"

#include "UIDemo/YCNDebugHelper.h"

void UYCNWidget_ListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (AnalogSlider_SettingSlider)
	{
		AnalogSlider_SettingSlider->OnValueChanged.AddDynamic(this, &UYCNWidget_ListEntry_Scalar::OnSettingSliderValueChanged);
		AnalogSlider_SettingSlider->OnMouseCaptureBegin.AddUniqueDynamic(this, &UYCNWidget_ListEntry_Scalar::OnSettingSliderMouseCaptureBegin);
	}
}

void UYCNWidget_ListEntry_Scalar::OnOwningListDataObjectSet(UYCNListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningScalarDataObject = Cast<UYCNListDataObject_Scalar>(InOwningListDataObject);
	if (CachedOwningScalarDataObject)
	{
		if (!CommonNumeric_SettingValue || !AnalogSlider_SettingSlider)return;

		CommonNumeric_SettingValue->SetNumericType(CachedOwningScalarDataObject->GetDisplayNumericType());
		CommonNumeric_SettingValue->FormattingSpecification = CachedOwningScalarDataObject->GetNumberFormattingOptions();
		CommonNumeric_SettingValue->SetCurrentValue(CachedOwningScalarDataObject->GetCurrentValue());
		
		AnalogSlider_SettingSlider->SetMinValue(CachedOwningScalarDataObject->GetDisplayValueRange().GetLowerBoundValue());
		AnalogSlider_SettingSlider->SetMaxValue(CachedOwningScalarDataObject->GetDisplayValueRange().GetUpperBoundValue());
		AnalogSlider_SettingSlider->SetStepSize(CachedOwningScalarDataObject->GetSliderStepSize());
		AnalogSlider_SettingSlider->SetValue(CachedOwningScalarDataObject->GetCurrentValue());

	}
}

void UYCNWidget_ListEntry_Scalar::OnOwningListDataObjectModified(UYCNListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason InModifyReason)
{
	if (CachedOwningScalarDataObject)
	{
		if (!CommonNumeric_SettingValue || !AnalogSlider_SettingSlider)return;

		CommonNumeric_SettingValue->SetCurrentValue(CachedOwningScalarDataObject->GetCurrentValue());
		AnalogSlider_SettingSlider->SetValue(CachedOwningScalarDataObject->GetCurrentValue());
	}
}

void UYCNWidget_ListEntry_Scalar::OnSettingSliderValueChanged(float NewValue)
{
	if (CachedOwningScalarDataObject)
	{
		CachedOwningScalarDataObject->SetCurrentValue(NewValue);
	}
}

void UYCNWidget_ListEntry_Scalar::OnSettingSliderMouseCaptureBegin()
{
	SelectThisEntryWidget();
}
