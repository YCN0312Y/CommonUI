// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/Components/YCNCommonButtonBase.h"
#include "CommonTextBlock.h"

void UYCNCommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
}

void UYCNCommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (CommonText_ButtonText)
	{
		CommonText_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
}

void UYCNCommonButtonBase::SetButtonText(const FText& InText)
{
	if (CommonText_ButtonText && !InText.IsEmpty())
	{
		CommonText_ButtonText->SetText(InText);
	}
}
