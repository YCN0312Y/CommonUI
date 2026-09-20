// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_KeyRemap.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_KeyRemap.h"
#include "UIDemo/Widgets/Components/YCNCommonButtonBase.h"
#include "UIDemo/Subsystems/YCNWidgetSubsystem.h"
#include "UIDemo/GameplayTags/YCNGameplayTags.h"
#include "UIDemo/FunctionLibrary/YCNFunctionLibrary.h"

void UYCNWidget_ListEntry_KeyRemap::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (CommonButton_RemapKey)
	{
		CommonButton_RemapKey->OnClicked().AddUObject(this, &UYCNWidget_ListEntry_KeyRemap::OnClickedRemapKey);
	}
	if (CommonButton_ResetKeyBinding)
	{
		CommonButton_ResetKeyBinding->OnClicked().AddUObject(this, &UYCNWidget_ListEntry_KeyRemap::OnResetKeyBindingClicked);
	}
}

void UYCNWidget_ListEntry_KeyRemap::OnOwningListDataObjectSet(UYCNListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningKeyRemapDataObject = CastChecked<UYCNListDataObject_KeyRemap>(InOwningListDataObject);
	CommonButton_RemapKey->SetButtonImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
}

void UYCNWidget_ListEntry_KeyRemap::OnOwningListDataObjectModified(UYCNListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason InModifyReason)
{
	if (!CachedOwningKeyRemapDataObject)return;
	CommonButton_RemapKey->SetButtonImage(CachedOwningKeyRemapDataObject->GetIconFromCurrentKey());
}

void UYCNWidget_ListEntry_KeyRemap::OnClickedRemapKey()
{
	UYCNWidgetSubsystem::Get(this)->PushSoftWidgetToStackAynsc(
		YCNGameplayTags::YCN_WidgetStack_Modal,
		UYCNFunctionLibrary::GetSoftWidgetClassByTag(YCNGameplayTags::YCN_Widget_KeyRemap),
		[](EAsyncPushWidgetState PushState, UYCNWidget_ActivatableBase* PushWidget)
		{

		});
}

void UYCNWidget_ListEntry_KeyRemap::OnResetKeyBindingClicked()
{

}
