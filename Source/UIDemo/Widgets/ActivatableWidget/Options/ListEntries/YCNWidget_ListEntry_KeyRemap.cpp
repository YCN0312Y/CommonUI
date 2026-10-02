// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/ListEntries/YCNWidget_ListEntry_KeyRemap.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_KeyRemap.h"
#include "UIDemo/Widgets/Components/YCNCommonButtonBase.h"
#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_KeyRemap.h"
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
	SelectThisEntryWidget();

	UYCNWidgetSubsystem::Get(this)->PushSoftWidgetToStackAynsc(
		YCNGameplayTags::YCN_WidgetStack_Modal,
		UYCNFunctionLibrary::GetSoftWidgetClassByTag(YCNGameplayTags::YCN_Widget_KeyRemap),
		[this](EAsyncPushWidgetState PushState, UYCNWidget_ActivatableBase* PushWidget)
		{
			if (PushState == EAsyncPushWidgetState::CreateWidget)
			{
				UYCNWidget_KeyRemap* CreatedKeyRemap = Cast<UYCNWidget_KeyRemap>(PushWidget);
				CreatedKeyRemap->OnKeyRemapKeyPressed.BindUObject(this, &UYCNWidget_ListEntry_KeyRemap::OnKeyToRemapPressed);
				CreatedKeyRemap->OnKeyRemapCanceled.BindUObject(this, &UYCNWidget_ListEntry_KeyRemap::OnKeyToRemapCanceled);

				if (CreatedKeyRemap)
				{
					if (CachedOwningKeyRemapDataObject)
					{
						CreatedKeyRemap->SetCachedDesiredInputType(CachedOwningKeyRemapDataObject->GetCachedDesiredInputKeyType());
					}
				}
			}
			
		});
}

void UYCNWidget_ListEntry_KeyRemap::OnResetKeyBindingClicked()
{
	SelectThisEntryWidget();

	if (CachedOwningKeyRemapDataObject && !CachedOwningKeyRemapDataObject->CanResetBackToDefaultVaule())
	{
		UYCNWidgetSubsystem::Get(this)->PushConfirmWindowToModalStackAynsc(
			EConfirmWindowType::OK,
			FText::FromString(TEXT("重置按键")),
			FText::FromString(CachedOwningKeyRemapDataObject->GetDataDisplayName().ToString() + TEXT("已是默认设置")),
			[](EConfirmWindowButtonType InButtonType) {});
		return;
	}

	UYCNWidgetSubsystem::Get(this)->PushConfirmWindowToModalStackAynsc(
		EConfirmWindowType::YesNo,
		FText::FromString(TEXT("重置按键")),
		FText::FromString(TEXT("确定要重置") + CachedOwningKeyRemapDataObject->GetDataDisplayName().ToString() + TEXT("的默认设置吗")),
		[this](EConfirmWindowButtonType InButtonType) 
		{
			if (InButtonType == EConfirmWindowButtonType::Confirm)
			{
				CachedOwningKeyRemapDataObject->TryResetBackToDefaultVaule();
			}
		});
}

void UYCNWidget_ListEntry_KeyRemap::OnKeyToRemapPressed(const FKey& PressedKey)
{
	if (CachedOwningKeyRemapDataObject)
	{
		CachedOwningKeyRemapDataObject->BindNewInputKey(PressedKey);
	}
}

void UYCNWidget_ListEntry_KeyRemap::OnKeyToRemapCanceled(const FString& CanceledReason)
{
	UYCNWidgetSubsystem::Get(this)->PushConfirmWindowToModalStackAynsc(
		EConfirmWindowType::OK,
		FText::FromString(TEXT("按键")),
		FText::FromString(CanceledReason),
		[](EConfirmWindowButtonType InButtonType){});
}
