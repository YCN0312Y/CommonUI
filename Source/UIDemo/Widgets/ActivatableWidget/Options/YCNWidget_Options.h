// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_ActivatableBase.h"
#include "YCNWidget_Options.generated.h"

class UYCNOptionsDataRegistry;
class UYCNTabListWidgetBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNWidget_Options : public UYCNWidget_ActivatableBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized()override;
	virtual void NativeOnActivated()override;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UYCNTabListWidgetBase>TabList_OptionsTabs;
	//重置按钮
	UPROPERTY(EditDefaultsOnly, Category = "YCN Option", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;
	//重置操作句柄
	FUIActionBindingHandle ResetActionHandle;
	//拥有的注册的数据
	UPROPERTY(Transient)
	TObjectPtr<UYCNOptionsDataRegistry>CreateOwningDataRegistry;
private:
	//重置按钮回调函数
	void OnResetBoundActionTriggered();
	//返回
	void OnBackBoundActionTriggered();
	UYCNOptionsDataRegistry* GetOwningDataRegistry();
	UFUNCTION()
	void OnOptionsTabSelected(FName TabID);
};
