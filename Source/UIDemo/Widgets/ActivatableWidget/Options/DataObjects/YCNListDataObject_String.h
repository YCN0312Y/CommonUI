// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Value.h"
#include "YCNListDataObject_String.generated.h"


UCLASS()
class UIDEMO_API UYCNListDataObject_String : public UYCNListDataObject_Value
{
	GENERATED_BODY()

protected:
	//UYCNListDataObject_Base继承函数
	virtual void OnDataObjectInitialized()override;
	
protected:
	//当前字符串值
	FString CurrentStringValue;
	//当前文本值
	FText CurrentTextValue;

	TArray<FString>AvailableOptionStringArray;
	TArray<FText>AvailableOptionTextArray;

protected:
	bool TrySetDisplayTextFromStringValue(const FString& InCurrentStringValue);

public:
	//动态添加选项
	void AddDynamicOption(const FString& InStringValue, const FText& InTextValue);
	//前进到下一个选项
	void AdvanceToNextOption();
	//返回到下一个选项
	void BackToLastOption();

	FORCEINLINE FText GetCurrentTextValue()const { return CurrentTextValue; }
	FORCEINLINE const TArray<FString>& GetAvailableOptionStringArray()const { return AvailableOptionStringArray; }
	FORCEINLINE const TArray<FText>& GetAvailableOptionTextArray()const { return AvailableOptionTextArray; }
};
