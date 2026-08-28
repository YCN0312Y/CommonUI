// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/Components/YCNCommonButtonBase.h"
#include "CommonTextBlock.h"
#include "UIDemo/Subsystems/YCNWidgetSubsystem.h"

void UYCNCommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
}

void UYCNCommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (CommonText_ButtonText && GetCurrentTextStyleClass())
	{
		CommonText_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
}

void UYCNCommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (!ButtonDescriptionText.IsEmpty())
	{
		UYCNWidgetSubsystem::Get(this)->OnButtonDescriptionTextUpdate.Broadcast(this, ButtonDescriptionText);
	}
}

void UYCNCommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	UYCNWidgetSubsystem::Get(this)->OnButtonDescriptionTextUpdate.Broadcast(this, FText::GetEmpty());

}

void UYCNCommonButtonBase::SetButtonText(const FText& InText)
{
	if (CommonText_ButtonText && !InText.IsEmpty())
	{
		CommonText_ButtonText->SetText(InText);
	}
}
