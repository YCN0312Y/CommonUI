// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_ActivatableBase.h"
#include "Framework/Application/IInputProcessor.h"
#include "CommonInputTypeEnum.h"
#include "YCNWidget_KeyRemap.generated.h"

class UCommonRichTextBlock;
class FKeyRemapInputPreprocessor;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNWidget_KeyRemap : public UYCNWidget_ActivatableBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnActivated()override;
	virtual void NativeOnDeactivated()override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock>CommonRichText_RemapMessage;

	//缓存输入的预处理器
	TSharedPtr<FKeyRemapInputPreprocessor>CachedInputPreprocessor;
	//缓存期望输入类型
	ECommonInputType CachedDesiredInputType;

public:
	void SetCachedDesiredInputType(ECommonInputType InDesiredInputType);
	ECommonInputType GetCachedDesiredInputType()const { return CachedDesiredInputType; }
};

class FKeyRemapInputPreprocessor : public IInputProcessor
{

public:
	FKeyRemapInputPreprocessor(ECommonInputType InInputType);

protected:
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)override;
	//按键按下事件
	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)override;
	//鼠标按下事件
	virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)override;

private:
	//缓存输入类型
	ECommonInputType CachedInputType;
};
