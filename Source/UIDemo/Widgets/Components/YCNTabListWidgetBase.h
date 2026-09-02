// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "YCNTabListWidgetBase.generated.h"

class UYCNCommonButtonBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNTabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()

protected:
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif

private:
	//仅限编辑器创建主标签页数量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "YCN Widget", meta = (AllowPrivateAccess = "true", ClampMin = "1", ClampMax = "10"))
	int32 DebugEditorPreviewTabCount = 3;
	//主标签类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "YCN Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UYCNCommonButtonBase>TabButtonEntryWidgetClass;

public:
	//请求注册标签
	void RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayText);
};
