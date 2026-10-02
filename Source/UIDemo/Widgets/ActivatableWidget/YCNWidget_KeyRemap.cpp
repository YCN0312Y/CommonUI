// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_KeyRemap.h"
#include "CommonRichTextBlock.h"

#include "UIDemo/YCNDebugHelper.h"

void UYCNWidget_KeyRemap::NativeOnActivated()
{
	Super::NativeOnActivated();

	CachedInputPreprocessor = MakeShared<FKeyRemapInputPreprocessor>(CachedDesiredInputType);
	CachedInputPreprocessor->OnKeyPressed.BindUObject(this, &UYCNWidget_KeyRemap::OnKeyPressed);
	CachedInputPreprocessor->OnKeyCanceled.BindUObject(this, &UYCNWidget_KeyRemap::OnKeyCanceled);
	FSlateApplication::Get().RegisterInputPreProcessor(CachedInputPreprocessor, 1);

	FString InputDeviceName;

	switch (CachedDesiredInputType)
	{
	case ECommonInputType::MouseAndKeyboard:
		InputDeviceName = TEXT("鼠标/键盘");
		break;
	}
	const FString DisplayRichMessage = FString::Printf(TEXT("<KeyRemapDefault>按任意键</> <KeyRemapHighLight>%s</> <KeyRemapDefault>按键</>"), *InputDeviceName);
	if (CommonRichText_RemapMessage)
	{
		CommonRichText_RemapMessage->SetText(FText::FromString(DisplayRichMessage));
	}
	
}

void UYCNWidget_KeyRemap::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	if (CachedInputPreprocessor)
	{
		FSlateApplication::Get().UnregisterInputPreProcessor(CachedInputPreprocessor);

		CachedInputPreprocessor.Reset();
	}
	
}

// 已按下
void UYCNWidget_KeyRemap::OnKeyPressed(const FKey& InPressedKey)
{
	RequestDeactivateWidget(
		[this, InPressedKey]()
		{
			OnKeyRemapKeyPressed.ExecuteIfBound(InPressedKey);
		});
}

// 取消按下
void UYCNWidget_KeyRemap::OnKeyCanceled(const FString& CanceledReason)
{
	RequestDeactivateWidget(
		[this, CanceledReason]()
		{
			OnKeyRemapCanceled.ExecuteIfBound(CanceledReason);
		});
}

void UYCNWidget_KeyRemap::RequestDeactivateWidget(TFunction<void()>PreDeactivateCallback)
{
	FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda(
		[PreDeactivateCallback, this](float DeltaTime)->bool
		{
			PreDeactivateCallback();

			DeactivateWidget();
			return false;
		}));
}

void UYCNWidget_KeyRemap::SetCachedDesiredInputType(ECommonInputType InDesiredInputType)
{
	CachedDesiredInputType = InDesiredInputType;
}

/*
* FKeyRemapInputPreprocessor
*/
FKeyRemapInputPreprocessor::FKeyRemapInputPreprocessor(ECommonInputType InInputType)
	:CachedInputType(InInputType)
{
	
}

void FKeyRemapInputPreprocessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)
{

}

bool FKeyRemapInputPreprocessor::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	ProcessPressedKey(InKeyEvent.GetKey());
	return true;
}

bool FKeyRemapInputPreprocessor::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	ProcessPressedKey(MouseEvent.GetEffectingButton());
	return true;
}

void FKeyRemapInputPreprocessor::ProcessPressedKey(const FKey& InPressedKey)
{
	if (InPressedKey == EKeys::Escape)
	{
		OnKeyCanceled.ExecuteIfBound(TEXT("按键设置已取消"));
		return;
	}

	switch (CachedInputType)
	{
	case ECommonInputType::MouseAndKeyboard:
		if (InPressedKey.IsGamepadKey())
		{
			//判断用户按下的是否是游戏手柄
			OnKeyCanceled.ExecuteIfBound(TEXT("检测到按下的是游戏手柄"));
			return;
		}
		break;
	}

	OnKeyPressed.ExecuteIfBound(InPressedKey);
}
