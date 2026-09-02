// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNOptionsDataRegistry.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Collection.h"

void UYCNOptionsDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab();
}

void UYCNOptionsDataRegistry::InitGameplayCollectionTab()
{
	UYCNListDataObject_Collection* GameplayTab = NewObject<UYCNListDataObject_Collection>();
	if (GameplayTab)
	{
		GameplayTab->SetDataID(FName("Gameplay"));
		GameplayTab->SetDataDisplayName(FText::FromString(TEXT("游戏玩法")));

		RegistryOptionsTabList.Add(GameplayTab);
	}
}

void UYCNOptionsDataRegistry::InitAudioCollectionTab()
{
	UYCNListDataObject_Collection* AudioTab = NewObject<UYCNListDataObject_Collection>();
	if (AudioTab)
	{
		AudioTab->SetDataID(FName("Audio"));
		AudioTab->SetDataDisplayName(FText::FromString(TEXT("音频")));

		RegistryOptionsTabList.Add(AudioTab);
	}
}

void UYCNOptionsDataRegistry::InitVideoCollectionTab()
{
	UYCNListDataObject_Collection* VideoTab = NewObject<UYCNListDataObject_Collection>();
	if (VideoTab)
	{
		VideoTab->SetDataID(FName("Video"));
		VideoTab->SetDataDisplayName(FText::FromString(TEXT("视频")));

		RegistryOptionsTabList.Add(VideoTab);
	}
}

void UYCNOptionsDataRegistry::InitControlCollectionTab()
{
	UYCNListDataObject_Collection* ControlTab = NewObject<UYCNListDataObject_Collection>();
	if (ControlTab)
	{
		ControlTab->SetDataID(FName("Control"));
		ControlTab->SetDataDisplayName(FText::FromString(TEXT("控制")));

		RegistryOptionsTabList.Add(ControlTab);
	}
}
