// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Base.h"
#include "CommonInputTypeEnum.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "YCNListDataObject_KeyRemap.generated.h"

class UEnhancedInputUserSettings;
class UEnhancedPlayerMappableKeyProfile;

UCLASS()
class UIDEMO_API UYCNListDataObject_KeyRemap : public UYCNListDataObject_Base
{
	GENERATED_BODY()
	
public:
	//初始化键映射数据
	void InitKeyRemapData(
		UEnhancedInputUserSettings* InOwningInputUserSettings,
		UEnhancedPlayerMappableKeyProfile* InOwningKeyProfile,
		ECommonInputType InDesiredInputKeyType,
		const FPlayerKeyMapping& InOwningPlayerKeyMapping);

	FSlateBrush GetIconFromCurrentKey()const;
private:
	//缓存拥有的输入用户设置
	UPROPERTY(Transient)
	TObjectPtr<UEnhancedInputUserSettings>CachedOwningInputUserSettings;
	//缓存拥有的按键配置文件
	UPROPERTY(Transient)
	TObjectPtr<UEnhancedPlayerMappableKeyProfile>CachedOwningKeyProfile;
	//缓存当前想要按键类型
	ECommonInputType CachedDesiredInputKeyType;
	//缓存拥有的映射名称
	FName CachedOwningMappingName;
	//缓存拥有的映射键插槽
	EPlayerMappableKeySlot CachedOwningMappableKeySlot;

private:
	FPlayerKeyMapping* GetOwningKeyMapping()const;
};
