// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Subsystems/YCNLoadingScreenSubsystem.h"
#include "UIDemo/Settings/YCNLoadingScreenSettings.h"
#include "UIDemo/Interfaces/YCNLoadingScreenInterface.h"
#include "PreLoadScreenManager.h"
#include "Blueprint/UserWidget.h"

bool UYCNLoadingScreenSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*>YCNClasss;
		GetDerivedClasses(GetClass(), YCNClasss);
		//当前不是专用服务器且没有派生类的时候才会真
		return YCNClasss.IsEmpty();
	}
	return false;
}

void UYCNLoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//地图开始加载之前触发
	FCoreUObjectDelegates::PreLoadMapWithContext.AddUObject(this, &UYCNLoadingScreenSubsystem::OnMapPreLoaded);
	//地图加载完成之后触发
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UYCNLoadingScreenSubsystem::OnMapPostLoaded);
	bTickEnabled = true;
}

void UYCNLoadingScreenSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PreLoadMapWithContext.RemoveAll(this);
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
}

//获取这个可 Tick 的游戏对象，所属的 UWorld
UWorld* UYCNLoadingScreenSubsystem::GetTickableGameObjectWorld() const
{
	UGameInstance* OwningGameInstacne = GetGameInstance();
	if (!OwningGameInstacne)return nullptr;
	//返回当前 GameInstance 的 World
	return OwningGameInstacne->GetWorld();
}

void UYCNLoadingScreenSubsystem::Tick(float DeltaTime)
{
	TryUpdateLoadingScreen();
}

//获取当前可 Tick 的对象的 Tick 类型
ETickableTickType UYCNLoadingScreenSubsystem::GetTickableTickType() const
{
	if (IsTemplate())
	{
		//如果是类模版对象就不 Tick
		return ETickableTickType::Never;
	}
	return ETickableTickType::Conditional;
}

bool UYCNLoadingScreenSubsystem::IsTickable() const
{
	//Tick没被禁用、游戏实例有效、有游戏客户端视口
	return bTickEnabled && GetGameInstance() && GetGameInstance()->GetGameViewportClient();
}

TStatId UYCNLoadingScreenSubsystem::GetStatId() const
{
	//给 UYCNLoadingScreenSubsystem 创建一个 Tick 性能统计项，放到 STATGROUP_Tickables 组里，然后把它的统计 ID 返回。
	RETURN_QUICK_DECLARE_CYCLE_STAT(UYCNLoadingScreenSubsystem, STATGROUP_Tickables);
}

void UYCNLoadingScreenSubsystem::OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName)
{
	if (WorldContext.OwningGameInstance != GetGameInstance())return;
	bTickEnabled = true;
	bIsCurrentlyLoadingMap = true;
	TryUpdateLoadingScreen();
}

void UYCNLoadingScreenSubsystem::OnMapPostLoaded(UWorld* LoadedWorld)
{
	if (LoadedWorld && LoadedWorld->GetGameInstance() == GetGameInstance())
	{
		bIsCurrentlyLoadingMap = false;
	}
}

void UYCNLoadingScreenSubsystem::TryUpdateLoadingScreen()
{
	//检查是否有正在运行的启动加载界面
	if (IsPreLoadScreenActive())return;

	//检查是否应该显示加载界面
	if (ShouldShowLoadingScreen())
	{
		//加载界面
		TryDisplayLoadingScreenIfNone();
		OnLoadingReasonUpdate.Broadcast(CurrendLoadingReason);
	}
	else
	{
		NotifyLoadingScreenVisibilityChanged(false);
		//加载完成 清除当前的加载界面
		TryRemoveLoadingScreen();
		HoldLoadingScreenStartUpTime = -1.f;
		bTickEnabled = false;
	}
}

bool UYCNLoadingScreenSubsystem::ShouldShowLoadingScreen()
{
	const UYCNLoadingScreenSettings* LoadSettings = GetDefault<UYCNLoadingScreenSettings>();
	if (GIsEditor && LoadSettings && !LoadSettings->bShouldLoadingScreenInEditor)
	{
		//如果在编辑器中显示该加载界面就返回false
		return false;
	}

	if (!GetGameInstance())return false;

	if (CheckTheNeedToShowLoadingScreen())
	{
		if (!GetGameInstance()->GetGameViewportClient())return false;
		//如果需要显示加载界面就设置为禁用世界渲染
		GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = true;

		return true;
	}
	CurrendLoadingReason = TEXT("等待纹理加载完成...");

	//不用显示加载屏幕了就启用世界渲染
	GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = false;

	const float CurrentTime = FPlatformTime::Seconds();
	if (HoldLoadingScreenStartUpTime < 0.0f)
	{
		//界面启动时间 < 0 就把当前时间赋值给启动时间
		HoldLoadingScreenStartUpTime = CurrentTime;
	}

	//经过时间 = 当前时间 - 开始时间
	const float ElapsedTime = CurrentTime - HoldLoadingScreenStartUpTime;

	if (ElapsedTime < LoadSettings->HoldLoadingScreenExtraSeconds)
	{
		return true;
	}

	return false;
}

//是否有正在运行的启动加载界面
bool UYCNLoadingScreenSubsystem::IsPreLoadScreenActive() const
{
	//负责存储所有已注册的预加载屏幕，并播放或停止它们的类
	FPreLoadScreenManager* PreLoadScreenManager = FPreLoadScreenManager::Get();

	//有效激活预加载屏幕
	return PreLoadScreenManager != nullptr ? PreLoadScreenManager->HasValidActivePreLoadScreen() : false;
}

bool UYCNLoadingScreenSubsystem::CheckTheNeedToShowLoadingScreen()
{
	if (bIsCurrentlyLoadingMap)
	{
		CurrendLoadingReason = TEXT("加载关卡中...");

		return true;
	}
	if (!GetGameInstance())return false;

	UWorld* OwningWorld = GetGameInstance()->GetWorld();

	if (!OwningWorld)
	{
		CurrendLoadingReason = TEXT("初始化世界中...");
		return true;

	}

	if (!OwningWorld->HasBegunPlay())
	{
		CurrendLoadingReason = TEXT("游戏世界尚未开始...");
		return true;
	}

	if (!OwningWorld->GetFirstPlayerController())
	{
		CurrendLoadingReason = TEXT("第一个玩家控制器尚未开始...");
		return true;
	}
	return false;
}

void UYCNLoadingScreenSubsystem::TryDisplayLoadingScreenIfNone()
{
	if(IsPreLoadScreenActive()) return;
	
	if (CachedCreatedLoadingScreenWidget)return;

	const UYCNLoadingScreenSettings* LoadSettings = GetDefault<UYCNLoadingScreenSettings>();
	if (LoadSettings)
	{
		TSubclassOf<UUserWidget> LoadedWidgetClass = LoadSettings->GetLoadingScreenWidgetClassChecked();
		if (LoadedWidgetClass)
		{
			UUserWidget* CreatedWidget = UUserWidget::CreateWidgetInstance(*GetGameInstance(), LoadedWidgetClass, NAME_None);
			if (CreatedWidget)
			{
				CachedCreatedLoadingScreenWidget = CreatedWidget->TakeWidget();
				GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(CachedCreatedLoadingScreenWidget.ToSharedRef(), 1000);
				NotifyLoadingScreenVisibilityChanged(true);
			}
		}
	}
}

void UYCNLoadingScreenSubsystem::TryRemoveLoadingScreen()
{
	if (!CachedCreatedLoadingScreenWidget)return;
	GetGameInstance()->GetGameViewportClient()->RemoveViewportWidgetContent(CachedCreatedLoadingScreenWidget.ToSharedRef());
	CachedCreatedLoadingScreenWidget.Reset();
}

void UYCNLoadingScreenSubsystem::NotifyLoadingScreenVisibilityChanged(bool bIsVisible)
{
	for (ULocalPlayer* ExistingLocalPlayer : GetGameInstance()->GetLocalPlayers())
	{
		if (!ExistingLocalPlayer)continue;
		
		if (APlayerController* PC = ExistingLocalPlayer->GetPlayerController(GetGameInstance()->GetWorld()))
		{
			HandleLoadingState<APlayerController>(bIsVisible, PC);

			if (APawn* OwningPawn = PC->GetPawn())
			{
				HandleLoadingState<APawn>(bIsVisible, OwningPawn);
			}
		}
	}
}
