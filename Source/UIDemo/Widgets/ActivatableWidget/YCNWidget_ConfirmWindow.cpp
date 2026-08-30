// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_ConfirmWindow.h"
#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "UIDemo/Widgets/Components/YCNCommonButtonBase.h"
#include "ICommonInputModule.h"

UYCNConfirmWindowInfoObject* UYCNConfirmWindowInfoObject::CreateOKWindow(const FText& InWindowTiele, const FText& InWindowMessage)
{
	UYCNConfirmWindowInfoObject* InfoObject = NewObject<UYCNConfirmWindowInfoObject>();
	if (InfoObject)
	{
		InfoObject->WindowTiele = InWindowTiele;
		InfoObject->WindowMessage = InWindowMessage;

		FConfirmWindowButtonInfo OKButtonInfo;
		OKButtonInfo.ConfirmWindowButtonType = EConfirmWindowButtonType::Confirm;
		OKButtonInfo.ButtonDisplayText = FText::FromString(TEXT("确认"));
		InfoObject->AvailableWindowButton.Add(OKButtonInfo);

		return InfoObject;
	}
	return nullptr;
}

UYCNConfirmWindowInfoObject* UYCNConfirmWindowInfoObject::CreateYesNoWindow(const FText& InWindowTiele, const FText& InWindowMessage)
{
	UYCNConfirmWindowInfoObject* InfoObject = NewObject<UYCNConfirmWindowInfoObject>();
	if (InfoObject)
	{
		InfoObject->WindowTiele = InWindowTiele;
		InfoObject->WindowMessage = InWindowMessage;

		FConfirmWindowButtonInfo YesButtonInfo;
		YesButtonInfo.ConfirmWindowButtonType = EConfirmWindowButtonType::Confirm;
		YesButtonInfo.ButtonDisplayText = FText::FromString(TEXT("确认"));

		FConfirmWindowButtonInfo NoButtonInfo;
		NoButtonInfo.ConfirmWindowButtonType = EConfirmWindowButtonType::Cencel;
		NoButtonInfo.ButtonDisplayText = FText::FromString(TEXT("取消"));

		InfoObject->AvailableWindowButton.Add(YesButtonInfo);
		InfoObject->AvailableWindowButton.Add(NoButtonInfo);

		return InfoObject;
	}
	return nullptr;
}

void UYCNWidget_ConfirmWindow::InitConfirmWindow(UYCNConfirmWindowInfoObject* InWindowInfoObject, TFunction<void(EConfirmWindowButtonType)> ClickedButtonCallback)
{
	if (!InWindowInfoObject && !CommonText_Title && !CommonText_Message && !DynamicEntryBox_Buttons)return;

	CommonText_Title->SetText(InWindowInfoObject->WindowTiele);
	CommonText_Message->SetText(InWindowInfoObject->WindowMessage);

	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		DynamicEntryBox_Buttons->Reset<UYCNCommonButtonBase>(
			[](UYCNCommonButtonBase& ExistingButton)
			{
				//清空点击的所有回调事件
				ExistingButton.OnClicked().Clear();
			});
	}
	if (InWindowInfoObject->AvailableWindowButton.IsEmpty())return;

	for (const FConfirmWindowButtonInfo& AvailableButtonInfo : InWindowInfoObject->AvailableWindowButton)
	{
		FDataTableRowHandle InputActionRowHandle;

		switch (AvailableButtonInfo.ConfirmWindowButtonType)
		{
		case EConfirmWindowButtonType::Closed:
			//默认返回键
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
		case EConfirmWindowButtonType::Cencel:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
		}
		UYCNCommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UYCNCommonButtonBase>();//创建条目
		AddedButton->SetButtonText(AvailableButtonInfo.ButtonDisplayText);
		AddedButton->SetTriggeringInputAction(InputActionRowHandle);//设置
		AddedButton->OnClicked().AddLambda(
			[this, ClickedButtonCallback, AvailableButtonInfo]()
			{
				ClickedButtonCallback(AvailableButtonInfo.ConfirmWindowButtonType);
				DeactivateWidget();//停用控件
			});
	}
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		//聚焦最后一个按钮
		DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}
}
