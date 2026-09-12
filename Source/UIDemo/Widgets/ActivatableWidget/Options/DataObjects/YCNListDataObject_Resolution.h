// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_String.h"
#include "YCNListDataObject_Resolution.generated.h"


UCLASS()
class UIDEMO_API UYCNListDataObject_Resolution : public UYCNListDataObject_String
{
	GENERATED_BODY()

protected:
	//UYCNListDataObject_Base继承函数
	virtual void OnDataObjectInitialized()override;
	
public:
	void InitResolutionValue();
};
