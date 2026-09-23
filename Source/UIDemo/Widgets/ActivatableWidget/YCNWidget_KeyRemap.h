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
	DECLARE_DELEGATE_OneParam(FOnKeyRemapKeyPressed, const FKey&);
	FOnKeyRemapKeyPressed OnKeyRemapKeyPressed;

	DECLARE_DELEGATE_OneParam(FOnKeyRemapKeySelectCanceled, const FString&);
	FOnKeyRemapKeySelectCanceled OnKeyRemapKeySelectCanceled;

private:
	void OnValidKeyPressedDelected(const FKey& InPressedKey);

	void OnKeySelectCanceled(const FString& CanceledReason);

	//请求请用控件
	void RequestDeactivateWidget(TFunction<void()>PreDectivateCallback);
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

public:
	DECLARE_DELEGATE_OneParam(FOnInputPreProcessorKeyPressed, const FKey&);
	FOnInputPreProcessorKeyPressed OnInputPreProcessorKeyPressed;

	DECLARE_DELEGATE_OneParam(FOnInputPreProcessorKeySelectCanceled, const FString&);
	FOnInputPreProcessorKeySelectCanceled OnInputPreProcessorKeySelectCanceled;

protected:
	void ProcessPressedKey(const FKey& InPressedKey);
};
