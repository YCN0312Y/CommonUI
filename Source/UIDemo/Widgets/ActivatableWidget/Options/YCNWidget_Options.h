// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/YCNWidget_ActivatableBase.h"
#include "YCNWidget_Options.generated.h"

class UYCNOptionsDataRegistry;
class UYCNTabListWidgetBase;
class UYCNCommonListViewBase;
class UYCNWidget_OptionsDetailsView;
class UYCNListDataObject_Base;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UIDEMO_API UYCNWidget_Options : public UYCNWidget_ActivatableBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized()override;
	virtual void NativeConstruct()override;
	virtual void NativeOnActivated()override;
	virtual void NativeOnDeactivated()override;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UYCNTabListWidgetBase>TabList_OptionsTabs;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UYCNCommonListViewBase>CommonListView_OptionsList;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UYCNWidget_OptionsDetailsView>DetailsView_ListEntryInfo;
	//重置按钮
	UPROPERTY(EditDefaultsOnly, Category = "YCN Option", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;
	//重置操作句柄
	FUIActionBindingHandle ResetActionHandle;
	//注册数据
	UPROPERTY(Transient)
	TObjectPtr<UYCNOptionsDataRegistry>CreateOwningDataRegistry;
	//可重置的子标题数组
	UPROPERTY(Transient)
	TArray<UYCNListDataObject_Base*>ResettableDataArray;
	bool bIsResettingData = false;
private:
	//重置按钮回调函数
	void OnResetBoundActionTriggered();
	//返回
	void OnBackBoundActionTriggered();
	//获取所属的数据注册表
	UYCNOptionsDataRegistry* GetOwningDataRegistry();
	//获取条目小部件类名
	FString TryGetEntryWidgetClassName(UObject* InOwningListItem);

	/***********回调函数***********/
	//TabList_OptionsTabs
	UFUNCTION()
	void OnOptionsTabSelected(FName TabID);

	//CommonListView_OptionsList
	void OnOptionsEntryWidgetGenerated(UUserWidget& InGeneratedItem);
	void OnOptionsListHovered(UObject* InHoveredItem, bool bWasHovered);
	void OnOptionsListSelection(UObject* InSelectionItem);
};
