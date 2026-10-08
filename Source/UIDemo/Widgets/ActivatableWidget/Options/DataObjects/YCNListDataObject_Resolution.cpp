// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Resolution.h"
#include "UIDemo/Msic/YCNOptionsDataInteractionHelper.h"
#include "UIDemo/Settings/YCNGameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"

void UYCNListDataObject_Resolution::OnDataObjectInitialized()
{
	Super::OnDataObjectInitialized();

	//基类已经按 getter 的值找到对应文本；找不到时（当前分辨率不在全屏分辨率列表里）直接显示数值
	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentTextValue = ResToValueText(UYCNGameUserSettings::Get()->GetScreenResolution());
	}
}

void UYCNListDataObject_Resolution::InitResolutionValue()
{
	TArray<FIntPoint>AvaialbleResolutions;//可用分辨率
	//获取支持的全屏分辨率
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(AvaialbleResolutions);

	AvaialbleResolutions.Sort(
		[](const FIntPoint& A, const FIntPoint& B)->bool
		{
			//从小往大排序
			return A.SizeSquared() < B.SizeSquared();
		});

	for (const FIntPoint& Resolution : AvaialbleResolutions)
	{
		//将遍历到的分辨率都添加到选项中
		AddDynamicOption(ResToValueString(Resolution), ResToValueText(Resolution));
	}

	MaxResolution = ResToValueString(AvaialbleResolutions.Last());
	SetDefaultStringValue(MaxResolution);//将最大的分辨率这是为默认值
}

FString UYCNListDataObject_Resolution::ResToValueString(const FIntPoint& InResolution)
{
	//这个字符串会被 PropertyPathHelpers 解析成 SetScreenResolution 的参数，必须是 FIntPoint 的文本格式
	return FString::Printf(TEXT("(X=%i,Y=%i)"), InResolution.X, InResolution.Y);
}

FText UYCNListDataObject_Resolution::ResToValueText(const FIntPoint& InResolution)
{
	return FText::FromString(FString::Printf(TEXT("%i x %i"), InResolution.X, InResolution.Y));
}
