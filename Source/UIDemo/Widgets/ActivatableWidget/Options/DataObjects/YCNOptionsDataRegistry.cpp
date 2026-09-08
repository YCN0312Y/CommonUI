// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNOptionsDataRegistry.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Collection.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_String.h"
#include "UIDemo/Msic/YCNOptionsDataInteractionHelper.h"
#include "UIDemo/FunctionLibrary/YCNFunctionLibrary.h"
#include "UIDemo/GameplayTags/YCNGameplayTags.h"
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
				const FString EasyString = TEXT("<HighLight>简单：</>敌人毫无威胁，资源十分充裕。你可以抛开战斗压力，专注欣赏剧情、探索世界，享受纯粹的惬意旅程。\n\n");
				const FString NormalString = TEXT("<HighLight>正常：</>最平衡、最具代入感的设计。保留了适当的游玩乐趣与成就感，只要掌握基础玩法，任何人都能顺畅通关。\n\n");
				const FString HardString = TEXT("<HighLight>困难：</>全面检验你的熟练度。敌人更聪明、攻防更出色，促使你深入挖掘连招、配装与战术配合，带来极高的回馈感。\n\n");
				const FString VeryHardString = TEXT("<HighLight>极难：</>专为追求极限的硬核玩家打造。极致的严谨度与专注度要求，把游戏机制发挥到极致，通关后成就感直接拉满。\n\n");
				const FString DifficultyString = EasyString + NormalString + HardString + VeryHardString;
				GameDifficulty->SetDescriptionRichText(FText::FromString(DifficultyString));
				GameDifficulty->AddDynamicOption(TEXT("Easy"), FText::FromString(TEXT("简单")));
				GameDifficulty->AddDynamicOption(TEXT("Normal"), FText::FromString(TEXT("正常")));
				GameDifficulty->AddDynamicOption(TEXT("Hard"), FText::FromString(TEXT("困难")));
				GameDifficulty->AddDynamicOption(TEXT("Very Hard"), FText::FromString(TEXT("极难")));
				GameDifficulty->SetDefaultStringValue(TEXT("Normal"));
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
				TestTab->SetSoftDescriptionImage(UYCNFunctionLibrary::GetOptionsSoftImageByTag(YCNGameplayTags::YCN_Image_TestImage));
				TestTab->SetDescriptionRichText(FText::FromString(TEXT("这只是一个测试标签")));
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
