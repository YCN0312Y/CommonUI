// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_Base.h"
#include "YCNWidget_ListEntry_Scalar.generated.h"

class UCommonNumericTextBlock;
class UAnalogSlider;
class UYCNListDataObject_Scalar;

UCLASS()
class UIDEMO_API UYCNWidget_ListEntry_Scalar : public UYCNWidget_ListEntry_Base
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized()override;
	//当前条目被分配了一个列表数据对象
	virtual void OnOwningListDataObjectSet(UYCNListDataObject_Base* InOwningListDataObject)override;
	//当前条目关联的数据被修改
	virtual void OnOwningListDataObjectModified(UYCNListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason InModifyReason)override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UCommonNumericTextBlock>CommonNumeric_SettingValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UAnalogSlider>AnalogSlider_SettingSlider;

	//缓存拥有的标量数据对象
	UPROPERTY(Transient)
	TObjectPtr<UYCNListDataObject_Scalar>CachedOwningScalarDataObject;

private:
	UFUNCTION()
	void OnSettingSliderValueChanged(float NewValue);
	UFUNCTION()
	void OnSettingSliderMouseCaptureBegin();
};
