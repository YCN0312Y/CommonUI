// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/YCNWidget_Options.h"
#include "Input/CommonUIInputTypes.h"
#include "ICommonInputModule.h"
#include "UIDemo/YCNDebugHelper.h"

void UYCNWidget_Options::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction, 
				true, 
				FSimpleDelegate::CreateUObject(this, &UYCNWidget_Options::OnResetBoundActionTriggered)));
	}

	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(), 
			true, 
			FSimpleDelegate::CreateUObject(this, &UYCNWidget_Options::OnBackBoundActionTriggered)));

}

void UYCNWidget_Options::OnResetBoundActionTriggered()
{
	Debug::Print(TEXT("重置"));
}

void UYCNWidget_Options::OnBackBoundActionTriggered()
{
	//返回上一个控件
	DeactivateWidget();
}
