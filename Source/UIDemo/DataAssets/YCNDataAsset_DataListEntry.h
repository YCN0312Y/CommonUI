// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "YCNDataAsset_DataListEntry.generated.h"

class UYCNListDataObject_Base;
class UYCNWidget_ListEntry_Base;

UCLASS()
class UIDEMO_API UYCNDataAsset_DataListEntry : public UDataAsset
{
	GENERATED_BODY()
	
private:
	//子数据控件列表
	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<UYCNListDataObject_Base>, TSubclassOf<UYCNWidget_ListEntry_Base>>DataObjectListEntryMap;

public:
	//根据数据对象查找子控件类
	TSubclassOf<UYCNWidget_ListEntry_Base>FindEntryWidgetClassByDataObject(UYCNListDataObject_Base* InDataObject)const;
};
