// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "YCNCommonButtonBase.generated.h"

class UCommonTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNCommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct()override;
	virtual void NativeOnCurrentTextStyleChanged() override;
	
private:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCommonTextBlock>CommonText_ButtonText;

	//按钮显示文本
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "YCN Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDisplayText;
	//按钮描述文本
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "YCN Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDescriptionText;

public:
	//设置按钮文本
	UFUNCTION(BlueprintCallable, Category = "YCN Button")
	void SetButtonText(const FText& InText);

};
