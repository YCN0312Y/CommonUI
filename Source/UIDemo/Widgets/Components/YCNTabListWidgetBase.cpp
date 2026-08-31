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
