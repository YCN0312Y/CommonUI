// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonListView.h"
#include "YCNCommonListViewBase.generated.h"

class UYCNDataAsset_DataListEntry;

UCLASS()
class UIDEMO_API UYCNCommonListViewBase : public UCommonListView
{
	GENERATED_BODY()

protected:
	//内部生成条目控件时
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif
	
private:
	//数据列表条目映射
	UPROPERTY(EditAnywhere, Category = "YCN Widget")
	TObjectPtr<UYCNDataAsset_DataListEntry>DataListEntryMapping;
};
