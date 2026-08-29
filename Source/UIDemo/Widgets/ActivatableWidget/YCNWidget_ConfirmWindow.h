// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_ActivatableBase.h"
#include "UIDemo/YCNEnumType.h"
#include "YCNWidget_ConfirmWindow.generated.h"

class UCommonTextBlock;
class UDynamicEntryBox;

USTRUCT(BlueprintType)
struct FConfirmWindowButtonInfo
{
	GENERATED_BODY()

	//确认弹窗按钮类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConfirmWindowButtonType ConfirmWindowButtonType = EConfirmWindowButtonType::UnKnown;
	//按钮显示文本
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonDisplayText;
};

UCLASS()
class UIDEMO_API UYCNConfirmWindowInfoObject : public UObject
{
	GENERATED_BODY()

public:
	//弹窗标题
	UPROPERTY(Transient)
	FText WindowTiele;
	//弹窗消息
	UPROPERTY(Transient)
	FText WindowMessage;
	//弹窗按钮列表
	UPROPERTY(Transient)
	TArray<FConfirmWindowButtonInfo>AvailableWindowButton;

public:
	static UYCNConfirmWindowInfoObject* CreateOKWindow(const FText& InWindowTiele, const FText& InWindowMessage);
	static UYCNConfirmWindowInfoObject* CreateYesNoWindow(const FText& InWindowTiele, const FText& InWindowMessage);
};

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNWidget_ConfirmWindow : public UYCNWidget_ActivatableBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock>CommonText_Title;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock>CommonText_Message;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox>DynamicEntryBox_Buttons;

public:
	//初始化确认弹窗
	void InitConfirmWindow(UYCNConfirmWindowInfoObject* InWindowInfoObject, TFunction<void(EConfirmWindowButtonType)>ClickedButtonCallback);
};
