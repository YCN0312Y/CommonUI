// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YCNWidget_OptionsDetailsView.generated.h"

class UCommonTextBlock;
class UCommonLazyImage;
class UCommonRichTextBlock;

UCLASS()
class UIDEMO_API UYCNWidget_OptionsDetailsView : public UUserWidget
{
	GENERATED_BODY()
	
private:
	//标题
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock>CommonText_Title;
	//描述图像
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonLazyImage>CommonImage_DescriptionImage;
	//描述文本
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock>CommonRichText_Description;
	//动态详情
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock>CommonRichText_DynamicDetails;
	//禁用原因
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock>CommonRichText_DisabledReason;

};

