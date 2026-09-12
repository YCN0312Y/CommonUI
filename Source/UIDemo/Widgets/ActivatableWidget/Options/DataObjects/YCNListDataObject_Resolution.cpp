// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Resolution.h"
#include "UIDemo/Msic/YCNOptionsDataInteractionHelper.h"
#include "Kismet/KismetSystemLibrary.h"

void UYCNListDataObject_Resolution::OnDataObjectInitialized()
{
	Super::OnDataObjectInitialized();

	if (DataDynamciGetter)
	{
		DataDynamciGetter->GetValudFromString();
	}
}

void UYCNListDataObject_Resolution::InitResolutionValue()
{
	TArray<FIntPoint>AvaialbleResolutions;//可用分辨率

	UKismetSystemLibrary::GetSupportedFullscreenResolutions(AvaialbleResolutions);

	for (const FIntPoint& Resolution : AvaialbleResolutions)
	{

	}
}
