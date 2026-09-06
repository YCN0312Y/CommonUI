// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Settings/YCNGameUserSettings.h"

UYCNGameUserSettings* UYCNGameUserSettings::Get()
{
	if (GEngine)
	{
		if (Cast<UYCNGameUserSettings>(GEngine->GetGameUserSettings()))
		{
			return Cast<UYCNGameUserSettings>(GEngine->GetGameUserSettings());
		}
	}

	return nullptr;
}