// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_ActivatableBase.h"
#include "YCNWidget_Options.generated.h"

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNWidget_Options : public UYCNWidget_ActivatableBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized()override;
	
private:
	//重置按钮
	UPROPERTY(EditDefaultsOnly, Category = "YCN Option", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;
private:
	//重置按钮回调函数
	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();
};
