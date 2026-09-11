// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "YCNGameUserSettings.generated.h"

UCLASS()
class UIDEMO_API UYCNGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:
	UYCNGameUserSettings();

	static UYCNGameUserSettings* Get();

private:
	//缓存游戏难度
	UPROPERTY(Config)
	FString CurrentGameDifficully;
	//缓存的主音量
	UPROPERTY(Config)
	float CachedMainVolume;
	//缓存的音乐音量
	UPROPERTY(Config)
	float CachedMusicVolume;
	//缓存的音效音量
	UPROPERTY(Config)
	float CachedSoundVolume;
	//缓存的背景音频
	UPROPERTY(Config)
	bool CachedBackgroundAudio;
	//缓存的是否启用HDR模式
	UPROPERTY(Config)
	bool CachedUseHDRAudioMode;
public:
	//设置缓存游戏难度
	UFUNCTION()
	void SetCurrentGameDifficully(const FString& NewDifficullyValue) { CurrentGameDifficully = NewDifficullyValue; }
	//获取缓存游戏难度
	UFUNCTION()
	FString GetCurrentGameDifficully()const { return CurrentGameDifficully; }

	//设置缓存的主音量
	UFUNCTION()
	void SetCachedMainVolume(const float& NewVolumeValue) { CachedMainVolume = NewVolumeValue; }
	//获取缓存的主音量
	UFUNCTION()
	float GetCachedMainVolume()const { return CachedMainVolume; }

	//设置缓存的音乐音量
	UFUNCTION()
	void SetCachedMusicVolume(const float& NewVolumeValue) { CachedMusicVolume = NewVolumeValue; }
	//获取缓存的音乐音量
	UFUNCTION()
	float GetCachedMusicVolume()const { return CachedMusicVolume; }

	//设置缓存的音效音量
	UFUNCTION()
	void SetCachedSoundVolume(const float& NewVolumeValue) { CachedSoundVolume = NewVolumeValue; }
	//获取缓存的音效音量
	UFUNCTION()
	float GetCachedSoundVolume()const { return CachedSoundVolume; }

	//设置缓存的背景音频
	UFUNCTION()
	void SetCachedBackgroundAudio(const bool& NewValue) { CachedBackgroundAudio = NewValue; }
	//获取缓存的背景音频
	UFUNCTION()
	bool GetCachedBackgroundAudio()const { return CachedBackgroundAudio; }

	//设置缓存的是否启用HDR模式
	UFUNCTION()
	void SetCachedUseHDRAudioMode(const bool& NewValue) { CachedUseHDRAudioMode = NewValue; }
	//获取缓存的是否启用HDR模式
	UFUNCTION()
	bool GetCachedUseHDRAudioMode()const { return CachedUseHDRAudioMode; }
};
