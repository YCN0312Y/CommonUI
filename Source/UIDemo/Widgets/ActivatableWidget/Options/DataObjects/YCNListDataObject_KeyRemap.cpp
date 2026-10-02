// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_KeyRemap.h"
#include "CommonInputBaseTypes.h"
#include "CommonInputSubsystem.h"

void UYCNListDataObject_KeyRemap::InitKeyRemapData(
	UEnhancedInputUserSettings* InOwningInputUserSettings, 
	UEnhancedPlayerMappableKeyProfile* InOwningKeyProfile, 
	ECommonInputType InDesiredInputKeyType, 
	const FPlayerKeyMapping& InOwningPlayerKeyMapping)
{
	CachedOwningInputUserSettings = InOwningInputUserSettings;
	CachedOwningKeyProfile = InOwningKeyProfile;
	CachedDesiredInputKeyType = InDesiredInputKeyType;
	CachedOwningMappingName = InOwningPlayerKeyMapping.GetMappingName();
	CachedOwningMappableKeySlot = InOwningPlayerKeyMapping.GetSlot();
}

FSlateBrush UYCNListDataObject_KeyRemap::GetIconFromCurrentKey() const
{
	if (CachedOwningInputUserSettings)
	{
		FSlateBrush FoundBrush;
		UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(CachedOwningInputUserSettings->GetLocalPlayer());
		if (CommonInputSubsystem)
		{
			const bool bHasFoundBrush = UCommonInputPlatformSettings::Get()->TryGetInputBrush(
				FoundBrush,
				GetOwningKeyMapping()->GetCurrentKey(),
				CachedDesiredInputKeyType,
				CommonInputSubsystem->GetCurrentGamepadName());
			if (bHasFoundBrush)
			{
				return FoundBrush;
			}
		}
	}
	return FSlateBrush();
}

bool UYCNListDataObject_KeyRemap::HasDefaultValue() const
{
	return GetOwningKeyMapping()->GetDefaultKey().IsValid();
}

bool UYCNListDataObject_KeyRemap::CanResetBackToDefaultVaule() const
{
	//IsCustomized如果当前的按键 != 默认键就返回真
	return HasDefaultValue() && GetOwningKeyMapping()->IsCustomized();
}

bool UYCNListDataObject_KeyRemap::TryResetBackToDefaultVaule()
{
	if (CanResetBackToDefaultVaule() && CachedOwningInputUserSettings)
	{
		GetOwningKeyMapping()->ResetToDefault();
		CachedOwningInputUserSettings->SaveSettings();
		NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);
		return true;
	}
	return false;
}

FPlayerKeyMapping* UYCNListDataObject_KeyRemap::GetOwningKeyMapping() const
{
	if (CachedOwningKeyProfile)
	{
		FMapPlayerKeyArgs KeyArgs;
		KeyArgs.MappingName = CachedOwningMappingName;
		KeyArgs.Slot = CachedOwningMappableKeySlot;
		return CachedOwningKeyProfile->FindKeyMapping(KeyArgs);
	}
	return nullptr;
}

void UYCNListDataObject_KeyRemap::BindNewInputKey(const FKey& InNewKey)
{
	if (!CachedOwningInputUserSettings)return;

	FMapPlayerKeyArgs KeyArgs;
	KeyArgs.MappingName = CachedOwningMappingName;
	KeyArgs.Slot = CachedOwningMappableKeySlot;
	KeyArgs.NewKey = InNewKey;

	FGameplayTagContainer Container;
	CachedOwningInputUserSettings->MapPlayerKey(KeyArgs, Container);
	CachedOwningInputUserSettings->SaveSettings();
	NotifyListDataModified(this);
}
