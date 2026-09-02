// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YCNListDataObject_Base.generated.h"

#define LIST_DATA_ACCESSOR(Type, Value)\
void Set##Value(const Type& InValue) { Value = InValue; }\
FORCEINLINE Type Get##Value()const { return Value; }


UCLASS()
class UIDEMO_API UYCNListDataObject_Base : public UObject
{
	GENERATED_BODY()
	
private:
	//数据ID
	FName DataID;
	//数据显示名称
	FText DataDisplayName;
	//富文本描述
	FText DescriptionRichText;
	//禁用时的富文本
	FText DisabledRichText;
	//描述图像
	TSoftObjectPtr<UTexture2D>SoftDescriptionImage;
	//父级数据
	UPROPERTY(Transient)
	TObjectPtr<UYCNListDataObject_Base>ParentData;

protected:
	//初始化数据对象
	virtual void OnDataObjectInitialized();
public:
	//子类重写函数
	virtual TArray<UYCNListDataObject_Base*>GetAllChildListData()const { return TArray<UYCNListDataObject_Base*>(); }
	//是否有任意子列表数据
	virtual bool HasAnyChildListData()const { return false; }
	//初始化数据对象
	void InitDataObject();

	LIST_DATA_ACCESSOR(FName, DataID);
	LIST_DATA_ACCESSOR(FText, DataDisplayName);
	LIST_DATA_ACCESSOR(FText, DescriptionRichText);
	LIST_DATA_ACCESSOR(FText, DisabledRichText);
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage);
	LIST_DATA_ACCESSOR(TObjectPtr<UYCNListDataObject_Base>, ParentData);
};
