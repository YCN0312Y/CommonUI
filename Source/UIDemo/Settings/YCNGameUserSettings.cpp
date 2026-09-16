// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Settings/YCNGameUserSettings.h"

UYCNGameUserSettings::UYCNGameUserSettings()
	:CachedMainVolume(2.f)
	,CachedMusicVolume(2.f)
	,CachedSoundVolume(2.f)
	,CachedBackgroundAudio(false)
	, CachedUseHDRAudioMode(false)
{

}

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

void UYCNGameUserSettings::SetCurrentDiaplayGamma(float InNewGamma)
{
	if (GEngine)
	{
		GEngine->DisplayGamma = InNewGamma;
	}
}

float UYCNGameUserSettings::GetCurrentDiaplayGamma() const
{
	if (GEngine)
	{
		return GEngine->GetDisplayGamma();
	}
	return 0.0f;
}
float UYCNGameUserSettings::GetCurrentResolutionScalePercent() const
{
	return ScalabilityQuality.ResolutionQuality;
}