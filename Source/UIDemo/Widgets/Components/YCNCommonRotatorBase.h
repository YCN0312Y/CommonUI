// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonRotator.h"
#include "YCNCommonRotatorBase.generated.h"

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNCommonRotatorBase : public UCommonRotator
{
	GENERATED_BODY()
	
public:
	//根据文本设置选中的选项
	void SetSelectedOptionByText(const FText& InTextOption);
};
