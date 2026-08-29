#pragma once

UENUM(BlueprintType)
enum class EConfirmWindowType : uint8
{
	OK,
	YesNo,
	UnKnown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConfirmWindowButtonType : uint8
{
	Confirm,
	Cencel,
	Closed,
	UnKnown UMETA(Hidden)
};