// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_KeyRemap.h"
#include "CommonRichTextBlock.h"

#include "UIDemo/YCNDebugHelper.h"

void UYCNWidget_KeyRemap::NativeOnActivated()
{
	Super::NativeOnActivated();

	CachedInputPreprocessor = MakeShared<FKeyRemapInputPreprocessor>(CachedDesiredInputType);
	FSlateApplication::Get().RegisterInputPreProcessor(CachedInputPreprocessor, 1);
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
	Debug::Print(FString::Printf(TEXT("按下的按键: %s"), *InKeyEvent.GetKey().GetDisplayName().ToString()));
	UEnum* StaticCommonInputType = StaticEnum<ECommonInputType>();
	
	Debug::Print(FString::Printf(TEXT("输入类型: %s"), *StaticCommonInputType->GetValueAsString(CachedInputType)));
	return true;
}

bool FKeyRemapInputPreprocessor::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	Debug::Print(FString::Printf(TEXT("按下的鼠标: %s"), *MouseEvent.GetEffectingButton().GetDisplayName().ToString()));

	return true;
}