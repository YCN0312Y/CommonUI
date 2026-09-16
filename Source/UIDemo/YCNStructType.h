#pragma once

#include "YCNStructType.generated.h"

//子标签在什么情况下禁用选项
USTRUCT()
struct FOptionDataEditConditionDescriptor
{
	GENERATED_BODY()

private:
	//判断现在是否禁用选项
	TFunction<bool()>EditConditionFunc;
	//禁用原因
	FString DisableRichReason;
	//禁用时是否强制改成指定值
	TOptional<FString>DisableValue;

public:
	/*
	* EditConditionFunc
	*/
	void SetEditConditionFunc(TFunction<bool()> InEditConditionFunc)
	{
		EditConditionFunc = InEditConditionFunc;
	}

	//编辑函数是否有效
	bool IsValid()const
	{
		//EditConditionFunc不为空则为真
		return EditConditionFunc != nullptr;
	}

	//默认所有设置都可以编辑，除非编辑条件不成立
	bool IsEditConditionMet()const
	{
		if (IsValid())
		{
			return EditConditionFunc();
		}
		return true;
	}

	/*
	* DisableRichReason
	*/
	//设置值
	void SetDisableRichReason(const FString& InDisableRichReason)
	{
		DisableRichReason = InDisableRichReason;
	}

	//获取值
	FString GetDisableRichReason()const 
	{ 
		return DisableRichReason; 
	}

	/*
	* DisabledForcedStringValue
	*/
	//获取禁用值是否有效
	bool HasDisableValue()const
	{
		return DisableValue.IsSet();
	}

	//设置值
	void SetDisableValue(const FString& InForcedValue)
	{
		DisableValue = InForcedValue;
	}

	//获取值
	FString GetDisableValue()const
	{
		return DisableValue.GetValue();
	}
};