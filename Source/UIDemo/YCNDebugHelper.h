// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

DEFINE_LOG_CATEGORY_STATIC(LogYCNProject, Display, All);

namespace Debug
{
	static void Print(const FString& Msg, int32 InKey = -1, const FColor& InColor = FColor::MakeRandomColor())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 5.0f, InColor, Msg);
			
			UE_LOG(LogYCNProject, Warning, TEXT("%s"), *Msg);
		}
	}
}