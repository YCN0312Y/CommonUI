
#include "UIDemo/Msic/YCNOptionsDataInteractionHelper.h"
#include "UIDemo/Settings/YCNGameUserSettings.h"

FYCNOptionsDataInteractionHelper::FYCNOptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath)
	:CachedDynamicFunctionPath(InSetterOrGetterFuncPath)
{
	CachedGameUserSettings = UYCNGameUserSettings::Get();
}

void FYCNOptionsDataInteractionHelper::SetValudFromString(const FString& InStringValue)
{
	//CachedGameUserSettings 中找到一个“变量/函数”，将 InStringValue 的值设置给找到的“变量/函数”
	PropertyPathHelpers::SetPropertyValueFromString(CachedGameUserSettings.Get(), CachedDynamicFunctionPath, InStringValue);
}

FString FYCNOptionsDataInteractionHelper::GetValudFromString() const
{
	FString OutStringValue;
	//CachedGameUserSettings 中找到一个“变量/函数”，将其值设置给OutStringValue
	PropertyPathHelpers::GetPropertyValueAsString(CachedGameUserSettings.Get(), CachedDynamicFunctionPath, OutStringValue);

	return OutStringValue;
}
