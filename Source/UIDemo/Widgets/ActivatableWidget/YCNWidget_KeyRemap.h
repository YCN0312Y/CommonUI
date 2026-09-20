// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_ActivatableBase.h"
#include "YCNWidget_KeyRemap.generated.h"

class UCommonRichTextBlock;

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
};
