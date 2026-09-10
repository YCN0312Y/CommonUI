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
};
