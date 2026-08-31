// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Base.h"
#include "YCNListDataObject_Collection.generated.h"


UCLASS()
class UIDEMO_API UYCNListDataObject_Collection : public UYCNListDataObject_Base
{
	GENERATED_BODY()

public:
	//获取所有子列表数据
	virtual TArray<UYCNListDataObject_Base*>GetAllChildListData()const override;
	//是否有任意子列表数据
	virtual bool HasAnyChildListData()const override;

private:
	//子数据列表
	UPROPERTY(Transient)
	TArray<UYCNListDataObject_Base*>ChildDataList;

public:
	//将数据添加到子数据列表
	void AddDataToChildDataList(UYCNListDataObject_Base* InData);
	
};
