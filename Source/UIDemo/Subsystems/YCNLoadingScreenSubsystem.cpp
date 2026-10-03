// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Subsystems/YCNLoadingScreenSubsystem.h"

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
	FCoreUObjectDelegates::PreLoadMapWithContext.AddUObject(this, &UYCNLoadingScreenSubsystem::OnMapPreLoaded);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UYCNLoadingScreenSubsystem::OnMapPostLoaded);
}

void UYCNLoadingScreenSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PreLoadMapWithContext.RemoveAll(this);
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
}

void UYCNLoadingScreenSubsystem::OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName)
{

}

void UYCNLoadingScreenSubsystem::OnMapPostLoaded(UWorld* LoadedWorld)
{

}
