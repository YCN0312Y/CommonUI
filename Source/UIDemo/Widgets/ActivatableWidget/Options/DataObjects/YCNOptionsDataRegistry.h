// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YCNOptionsDataRegistry.generated.h"

class UYCNListDataObject_Collection;
class UYCNListDataObject_Base;

UCLASS()
class UIDEMO_API UYCNOptionsDataRegistry : public UObject
{
	GENERATED_BODY()

private:
	//已注册的选项主标签列表
	UPROPERTY(Transient)
	TArray<UYCNListDataObject_Collection*>RegistryOptionsTabList;

private:
	//初始化标签
	void InitGameplayCollectionTab();
	void InitAudioCollectionTab();
	void InitVideoCollectionTab();
	void InitControlCollectionTab();

public:
	//初始化选项注册的数据
	void InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer);

	//根据选定的标签 ID 获取列表源数据
	TArray<UYCNListDataObject_Base*>GetListSourceItemBySelectedTabID(const FName& IsSelectedTabID);

	FORCEINLINE const TArray<UYCNListDataObject_Collection*>&GetRegistryOptionsTabList()const { return RegistryOptionsTabList; }
};
