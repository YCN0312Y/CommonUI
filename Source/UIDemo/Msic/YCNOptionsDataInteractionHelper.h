
#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"

class UYCNGameUserSettings;

class UIDEMO_API FYCNOptionsDataInteractionHelper
{
public:
	FYCNOptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath);

private:
	//缓存查询路径
	FCachedPropertyPath CachedDynamicFunctionPath;
	//缓存的游戏用户设置
	TWeakObjectPtr<UYCNGameUserSettings>CachedGameUserSettings;

public:
	void SetValudFromString(const FString& InStringValue);
	FString GetValudFromString()const;
};