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
	static UYCNGameUserSettings* Get();

private:
	//当前游戏难度
	UPROPERTY(Config)
	FString CurrentGameDifficully;

public:
	//设置当前游戏难度
	UFUNCTION()
	void SetCurrentGameDifficully(const FString& NewDifficullyValue) { CurrentGameDifficully = NewDifficullyValue; }
	//获取当前游戏难度
	UFUNCTION()
	FString GetCurrentGameDifficully()const { return CurrentGameDifficully; }
};
