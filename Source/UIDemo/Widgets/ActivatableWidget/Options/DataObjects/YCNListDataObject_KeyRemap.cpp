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
