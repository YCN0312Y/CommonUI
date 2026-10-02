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
	//按键按下时
	DECLARE_DELEGATE_OneParam(FOnKeyRemapKeyPressed, const FKey&);
	FOnKeyRemapKeyPressed OnKeyRemapKeyPressed;
	//取消
	DECLARE_DELEGATE_OneParam(FOnKeyRemapKeySelectCanceled, const FString&);
	FOnKeyRemapKeySelectCanceled OnKeyRemapCanceled;

private:
	void OnKeyPressed(const FKey& InPressedKey);

	void OnKeyCanceled(const FString& CanceledReason);

	//请求请用控件
	void RequestDeactivateWidget(TFunction<void()>PreDectivateCallback);
public:
	void SetCachedDesiredInputType(ECommonInputType InDesiredInputType);
	ECommonInputType GetCachedDesiredInputType()const { return CachedDesiredInputType; }

};

//按键输入预处理器
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

public:
	//按下
	DECLARE_DELEGATE_OneParam(FOnKeyPressed, const FKey&);
	FOnKeyPressed OnKeyPressed;
	//取消
	DECLARE_DELEGATE_OneParam(FOnKeyCanceled, const FString&);
	FOnKeyCanceled OnKeyCanceled;

protected:
	//处理按下的键
	void ProcessPressedKey(const FKey& InPressedKey);
};
