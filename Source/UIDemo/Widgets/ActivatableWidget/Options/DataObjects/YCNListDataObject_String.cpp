// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_String.h"
#include "UIDemo/Msic/YCNOptionsDataInteractionHelper.h"

void UYCNListDataObject_String::OnDataObjectInitialized()
{
	if (!AvailableOptionStringArray.IsEmpty())
	{
		CurrentStringValue = AvailableOptionStringArray[0];
	}

	if (DataDynamciGetter)
	{
		if (!DataDynamciGetter->GetValudFromString().IsEmpty())
		{
			//如果 GameUserSetting 中保存的 CurrentGameDifficully 不为空，就设置给当前字符串
			CurrentStringValue = DataDynamciGetter->GetValudFromString();
		}
	}
	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		//如果查到的索引不在 AvailableOptionTextArray 中那就是无效索引
		CurrentTextValue = FText::FromString(TEXT("无效的选项"));
	}
}

void UYCNListDataObject_String::AddDynamicOption(const FString& InStringValue, const FText& InTextValue)
{
	if (InStringValue.IsEmpty() || InTextValue.IsEmpty())return;

	AvailableOptionStringArray.Add(InStringValue);
	AvailableOptionTextArray.Add(InTextValue);
}

void UYCNListDataObject_String::AdvanceToNextOption()
{
	if (AvailableOptionStringArray.IsEmpty() || AvailableOptionTextArray.IsEmpty())return;

	const int32 CurrentDisplayIndex = AvailableOptionStringArray.IndexOfByKey(CurrentStringValue);
	const int32 NextDisplayIndex = CurrentDisplayIndex + 1;

	const bool bIsNextIndexValid = AvailableOptionStringArray.IsValidIndex(NextDisplayIndex);
	if (bIsNextIndexValid)
	{
		CurrentStringValue = AvailableOptionStringArray[NextDisplayIndex];
	}
	else
	{
		CurrentStringValue = AvailableOptionStringArray[0];
	}

	TrySetDisplayTextFromStringValue(CurrentStringValue);

	if (DataDynamciSetter)
	{
		//将 CurrentStringValue 的游戏难度设置缓存到 GameUserSettings 中
		DataDynamciSetter->SetValudFromString(CurrentStringValue);
		NotifyListDataModified(this);
	}

}

void UYCNListDataObject_String::BackToLastOption()
{
	if (AvailableOptionStringArray.IsEmpty() || AvailableOptionTextArray.IsEmpty())return;

	//当前显示的文本索引
	const int32 CurrentDisplayIndex = AvailableOptionStringArray.IndexOfByKey(CurrentStringValue);
	const int32 LastDisplayIndex = CurrentDisplayIndex - 1;//上一个文本索引

	const bool bIsLastIndexValid = AvailableOptionStringArray.IsValidIndex(LastDisplayIndex);
	if (bIsLastIndexValid)
	{
		//上一个文本索引有效，那么当前字符串值，就为字符串列表中上一个文本索引的字符
		CurrentStringValue = AvailableOptionStringArray[LastDisplayIndex];
	}
	else
	{
		//上一个文本索引无效，就为字符串列表中最后文本索引的字符，设置给当前字符串值
		CurrentStringValue = AvailableOptionStringArray.Last();
	}

	TrySetDisplayTextFromStringValue(CurrentStringValue);

	if (DataDynamciSetter)
	{
		//将 CurrentStringValue 的游戏难度设置缓存到 GameUserSettings 中
		DataDynamciSetter->SetValudFromString(CurrentStringValue);
		NotifyListDataModified(this);
	}
}

bool UYCNListDataObject_String::TrySetDisplayTextFromStringValue(const FString& InCurrentStringValue)
{
	//根据传进来的字符串，查到当前所在索引
	const int32 CurrentFoundIndex = AvailableOptionStringArray.IndexOfByKey(InCurrentStringValue);

	if (AvailableOptionTextArray.IsValidIndex(CurrentFoundIndex))
	{
		//如果查到的索引有效就将这个索引的文本值设置给当前显示文本
		CurrentTextValue = AvailableOptionTextArray[CurrentFoundIndex];

		return true;
	}
	return false;
}
