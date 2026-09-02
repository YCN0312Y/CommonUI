// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/Components/YCNTabListWidgetBase.h"
#include "Editor/WidgetCompilerLog.h"
#include "UIDemo/Widgets/Components/YCNCommonButtonBase.h"

#if WITH_EDITOR	
void UYCNTabListWidgetBase::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!IsValid(TabButtonEntryWidgetClass))
	{
		CompileLog.Error(FText::FromString("TabButtonEntryWidgetClass为空"));
	}
}
#endif

void UYCNTabListWidgetBase::RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayText)
{
	//注册标签
	RegisterTab(InTabID, TabButtonEntryWidgetClass, nullptr, INDEX_NONE);

	UYCNCommonButtonBase* FoundButton = Cast<UYCNCommonButtonBase>(GetTabButtonBaseByID(InTabID));
	if (FoundButton)
	{
		FoundButton->SetButtonText(InTabDisplayText);
	}
}
