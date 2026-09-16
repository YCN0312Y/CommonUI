// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Base.h"
#include "UIDemo/Settings/YCNGameUserSettings.h"

void UYCNListDataObject_Base::OnDataObjectInitialized()
{

}

void UYCNListDataObject_Base::NotifyListDataModified(UYCNListDataObject_Base* InModifiedData, EOptionsListDataModifyReason InModifyReason)
{
	OnListDataModified.Broadcast(InModifiedData, InModifyReason);

	if (bApplyImmediately)
	{
		UYCNGameUserSettings::Get()->ApplySettings(true);
	}
}

void UYCNListDataObject_Base::OnEditDependencyDataModified(UYCNListDataObject_Base* InModifiedData, EOptionsListDataModifyReason InModifyReason)
{
	if (!InModifiedData)return;

	OnDependencyDataModified.Broadcast(InModifiedData, InModifyReason);
}

void UYCNListDataObject_Base::InitDataObject()
{
	OnDataObjectInitialized();
}

void UYCNListDataObject_Base::AddEditCondition(const FOptionDataEditConditionDescriptor& InEditCondition)
{
	EditConditionArray.Add(InEditCondition);
}

void UYCNListDataObject_Base::AddEditDependencyData(UYCNListDataObject_Base* InDependencyData)
{
	if (InDependencyData && !InDependencyData->OnListDataModified.IsBoundToObject(this))
	{
		//UYCNListDataObject_StringEnum
		InDependencyData->OnListDataModified.AddUObject(this, &UYCNListDataObject_Base::OnEditDependencyDataModified);
	}
}

bool UYCNListDataObject_Base::IsCurrentDataDisabled()
{
	bool bIsEditable = true;
	FString CachedDisableRichReason;

	for (const FOptionDataEditConditionDescriptor& Condition : EditConditionArray)
	{
		//编辑函数变量无效/这个选项没有被禁用就继续
		if (!Condition.IsValid() || Condition.IsEditConditionMet())continue;

		bIsEditable = false;
		//设置禁用原因
		CachedDisableRichReason.Append(Condition.GetDisableRichReason());
		SetDisabledRichText(FText::FromString(CachedDisableRichReason));

		if (Condition.HasDisableValue())
		{
			const FString ForcedStringValue = Condition.GetDisableValue();
			if (CanSetDisableValue(ForcedStringValue))
			{
				//如果禁用值有效且可以设置禁用值就将禁用值设置为这个选项的当前值
				OnSetDisableValue(ForcedStringValue);
			}
		}
	}

	return bIsEditable;
}
