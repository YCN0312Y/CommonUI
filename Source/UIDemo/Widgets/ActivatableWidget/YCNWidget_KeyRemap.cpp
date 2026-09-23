// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_KeyRemap.h"
#include "CommonRichTextBlock.h"

#include "UIDemo/YCNDebugHelper.h"

void UYCNWidget_KeyRemap::NativeOnActivated()
{
	Super::NativeOnActivated();

	CachedInputPreprocessor = MakeShared<FKeyRemapInputPreprocessor>(CachedDesiredInputType);
	CachedInputPreprocessor->OnInputPreProcessorKeyPressed.BindUObject(this, &UYCNWidget_KeyRemap::OnValidKeyPressedDelected);
	CachedInputPreprocessor->OnInputPreProcessorKeySelectCanceled.BindUObject(this, &UYCNWidget_KeyRemap::OnKeySelectCanceled);
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

void UYCNWidget_KeyRemap::OnValidKeyPressedDelected(const FKey& InPressedKey)
{
	RequestDeactivateWidget(
		[this, InPressedKey]()
		{
			OnKeyRemapKeyPressed.ExecuteIfBound(InPressedKey);
		});
}

void UYCNWidget_KeyRemap::OnKeySelectCanceled(const FString& CanceledReason)
{
	RequestDeactivateWidget(
		[this, CanceledReason]()
		{
			OnKeyRemapKeySelectCanceled.ExecuteIfBound(CanceledReason);
		});
}

void UYCNWidget_KeyRemap::RequestDeactivateWidget(TFunction<void()>PreDectivateCallback)
{
	FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda(
		[PreDectivateCallback, this](float DeltaTime)->bool
		{
			PreDectivateCallback();

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
		OnInputPreProcessorKeySelectCanceled.ExecuteIfBound(TEXT("按键设置已取消"));
		return;
	}

	switch (CachedInputType)
	{
	case ECommonInputType::MouseAndKeyboard:
		if (InPressedKey.IsGamepadKey())
		{
			OnInputPreProcessorKeySelectCanceled.ExecuteIfBound(TEXT("检测到按下的是游戏手柄"));
			return;
		}
		break;
	}

	OnInputPreProcessorKeyPressed.ExecuteIfBound(InPressedKey);
}
