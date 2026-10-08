// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIDemo/Interfaces/YCNLoadingScreenInterface.h"
#include "YCNLoadingScreenSubsystem.generated.h"

UCLASS()
class UIDEMO_API UYCNLoadingScreenSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection)override;

	virtual void Deinitialize()override;

	/*
	* FTickableGameObject
	*/
	//获取这个可 Tick 的游戏对象，所属的 UWorld
	virtual UWorld* GetTickableGameObjectWorld() const override;

	virtual void Tick(float DeltaTime)override;

	//获取这个可 Tick 对象的 Tick 类型
	virtual ETickableTickType GetTickableTickType() const override;

	//当前这个对象现在是否可以执行 Tick
	virtual bool IsTickable() const override;

	//这个 Tickable 对象的 Tick 性能开销，应该记到哪个统计项里。
	virtual TStatId GetStatId() const override;
	
public:
	//更新加载原因
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadingReasonUpdate, const FString&, CurrendLoadingReason);
	UPROPERTY(BlueprintAssignable)
	FOnLoadingReasonUpdate OnLoadingReasonUpdate;

private:
	//是否禁用Tick
	bool bTickEnabled = false;

	//当前是否正在加载地图
	bool bIsCurrentlyLoadingMap = false;

	//保持加载界面启动时间
	float HoldLoadingScreenStartUpTime = -1.0f;

	//当前加载原因
	FString CurrendLoadingReason;

	//缓存创建的加载界面控件
	TSharedPtr<SWidget>CachedCreatedLoadingScreenWidget;
private:
	void OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName);

	void OnMapPostLoaded(UWorld* LoadedWorld);

	//尝试更新加载界面
	void TryUpdateLoadingScreen();

	bool ShouldShowLoadingScreen();

	//是否有正在运行的启动加载界面
	bool IsPreLoadScreenActive()const;

	//检查是否需要显示加载界面
	bool CheckTheNeedToShowLoadingScreen();

	//如果为空则尝试显示加载界面
	void TryDisplayLoadingScreenIfNone();

	//尝试移除机载屏幕
	void TryRemoveLoadingScreen();

	void NotifyLoadingScreenVisibilityChanged(bool bIsVisible);

	template<typename Type>
	void HandleLoadingState(bool bIsVisible, Type* InType)
	{
		if (InType->Implements<UYCNLoadingScreenInterface>())
		{
			if (bIsVisible)
			{
				IYCNLoadingScreenInterface::Execute_OnLoadingScreenActivated(InType);
			}
			else
			{
				IYCNLoadingScreenInterface::Execute_OnLoadingScreenDeactivated(InType);
			}
		}
	}
};
