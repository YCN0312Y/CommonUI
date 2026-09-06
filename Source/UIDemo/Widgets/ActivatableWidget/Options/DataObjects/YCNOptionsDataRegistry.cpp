// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNOptionsDataRegistry.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Collection.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_String.h"
#include "UIDemo/Msic/YCNOptionsDataInteractionHelper.h"
#include "UIDemo/Settings/YCNGameUserSettings.h"

#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGatterFuncName)\
MakeShared<FYCNOptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UYCNGameUserSettings, SetterOrGatterFuncName))

void UYCNOptionsDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab();
}

TArray<UYCNListDataObject_Base*> UYCNOptionsDataRegistry::GetListSourceItemBySelectedTabID(const FName& IsSelectedTabID)
{
	UYCNListDataObject_Collection* const* FoundTabCollectionPtr = RegistryOptionsTabList.FindByPredicate(
		[IsSelectedTabID](UYCNListDataObject_Collection* AvailableTabCollection)
		{
			//遍历 RegistryOptionsTabList 如果遍历到的数据ID == 传进来的ID就返回这个数据
			return AvailableTabCollection->GetDataID() == IsSelectedTabID;
		});
	if (!FoundTabCollectionPtr)return TArray<UYCNListDataObject_Base*>();

	UYCNListDataObject_Collection* FoundTabCollection = *FoundTabCollectionPtr;
	//返回遍历到正确ID的子数据列表
	return FoundTabCollection->GetAllChildListData();
}

void UYCNOptionsDataRegistry::InitGameplayCollectionTab()
{
	UYCNListDataObject_Collection* GameplayTab = NewObject<UYCNListDataObject_Collection>();
	if (GameplayTab)
	{
		GameplayTab->SetDataID(FName("Gameplay"));
		GameplayTab->SetDataDisplayName(FText::FromString(TEXT("游戏玩法")));

		RegistryOptionsTabList.Add(GameplayTab);
		//游戏难度标签
		{
			UYCNListDataObject_String* GameDifficulty = NewObject<UYCNListDataObject_String>();
			if (GameDifficulty)
			{
				GameDifficulty->SetDataID(FName("GameDifficulty"));
				GameDifficulty->SetDataDisplayName(FText::FromString(TEXT("游戏难度")));
				GameDifficulty->AddDynamicOption(TEXT("Easy"), FText::FromString(TEXT("简单")));
				GameDifficulty->AddDynamicOption(TEXT("Normal"), FText::FromString(TEXT("正常")));
				GameDifficulty->AddDynamicOption(TEXT("Hard"), FText::FromString(TEXT("困难")));
				GameDifficulty->AddDynamicOption(TEXT("Very Hard"), FText::FromString(TEXT("极难")));
				GameDifficulty->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentGameDifficully));
				GameDifficulty->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentGameDifficully));
				//将 “游戏难度” 子标签添加给主标签 “游戏玩法”
				GameplayTab->AddDataToChildDataList(GameDifficulty);
			}
		}
		//测试标签
		{
			UYCNListDataObject_String* TestTab = NewObject<UYCNListDataObject_String>();
			if (TestTab)
			{
				TestTab->SetDataID(FName("TestTab"));
				TestTab->SetDataDisplayName(FText::FromString(TEXT("测试标签")));

				GameplayTab->AddDataToChildDataList(TestTab);
			}
		}
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
