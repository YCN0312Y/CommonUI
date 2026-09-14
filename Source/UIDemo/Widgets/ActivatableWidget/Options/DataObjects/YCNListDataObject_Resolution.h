// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_String.h"
#include "YCNListDataObject_Resolution.generated.h"


UCLASS()
class UIDEMO_API UYCNListDataObject_Resolution : public UYCNListDataObject_String
{
	GENERATED_BODY()

protected:
	//UYCNListDataObject_Base继承函数
	virtual void OnDataObjectInitialized()override;	
public:
	//初始化分辨率值
	void InitResolutionValue();
	//获取最大分辨率
	FString GetMaxResolution()const { return MaxResolution; }
private:
	//分辨率值转FString
	FString ResToValueString(const FIntPoint& InResolution);
	//分辨率值转FText
	FText ResToValueText(const FIntPoint& InResolution);
	//最大分辨率
	FString MaxResolution;

};
