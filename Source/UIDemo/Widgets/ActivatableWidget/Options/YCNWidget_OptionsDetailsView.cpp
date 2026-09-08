// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/YCNWidget_OptionsDetailsView.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Base.h"
#include "CommonTextBlock.h"
#include "CommonLazyImage.h"
#include "CommonRichTextBlock.h"

void UYCNWidget_OptionsDetailsView::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ClearDetailsViewInfo();
}

void UYCNWidget_OptionsDetailsView::UpdateDetailsViewInfo(UYCNListDataObject_Base* InDataObject, const FString& InEntryWidgetClassName)
{
	if (!InDataObject || !CommonText_Title || !CommonImage_DescriptionImage || !CommonRichText_Description || !CommonRichText_DynamicDetails || !CommonRichText_DisabledReason)return;

	CommonText_Title->SetText(InDataObject->GetDataDisplayName());

	if (InDataObject->GetSoftDescriptionImage().IsValid())
	{
		CommonImage_DescriptionImage->SetBrushFromLazyTexture(InDataObject->GetSoftDescriptionImage());
		CommonImage_DescriptionImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		CommonImage_DescriptionImage->SetVisibility(ESlateVisibility::Collapsed);
	}
	CommonRichText_Description->SetText(InDataObject->GetDescriptionRichText());
	const FString DynamicDetails = FString::Printf(TEXT("<HighLight>数据对象类: </>%s"), *InEntryWidgetClassName);
	CommonRichText_DynamicDetails->SetText(FText::FromString(DynamicDetails));
	CommonRichText_DisabledReason->SetText(InDataObject->GetDisabledRichText());
}

void UYCNWidget_OptionsDetailsView::ClearDetailsViewInfo()
{
	if (!CommonText_Title || !CommonImage_DescriptionImage || !CommonRichText_Description || !CommonRichText_DynamicDetails || !CommonRichText_DisabledReason)return;
	
	CommonText_Title->SetText(FText::GetEmpty());
	CommonImage_DescriptionImage->SetVisibility(ESlateVisibility::Collapsed);
	CommonRichText_Description->SetText(FText::GetEmpty());
	CommonRichText_DynamicDetails->SetText(FText::GetEmpty());
	CommonRichText_DisabledReason->SetText(FText::GetEmpty());
}
