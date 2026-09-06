#pragma once

//确认窗口类型
UENUM(BlueprintType)
enum class EConfirmWindowType : uint8
{
	OK,
	YesNo,
	UnKnown UMETA(Hidden)
};

//确认窗口按钮类型
UENUM(BlueprintType)
enum class EConfirmWindowButtonType : uint8
{
	Confirm,
	Cencel,
	Closed,
	UnKnown UMETA(Hidden)
};

//选项列表数据修改原因
UENUM(BlueprintType)
enum class EOptionsListDataModifyReason : uint8
{
	//直接修改
	DirectlyModified,
	//依赖/间接修改
	DependencyModified,
	//重置为默认值
	ResetToDefault
};