// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNOptionsDataRegistry.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Collection.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_String.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Scalar.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_Resolution.h"
#include "UIDemo/Widgets/ActivatableWidget/Options/DataObjects/YCNListDataObject_KeyRemap.h"
#include "UIDemo/Msic/YCNOptionsDataInteractionHelper.h"
#include "UIDemo/FunctionLibrary/YCNFunctionLibrary.h"
#include "UIDemo/GameplayTags/YCNGameplayTags.h"
#include "UIDemo/Settings/YCNGameUserSettings.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "UIDemo/YCNDebugHelper.h"

#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGatterFuncName)\
MakeShared<FYCNOptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UYCNGameUserSettings, SetterOrGatterFuncName))

void UYCNOptionsDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab(InOwningLocalPlayer);
}

TArray<UYCNListDataObject_Base*> UYCNOptionsDataRegistry::GetListSourceItemBySelectedTabID(const FName& InSelectedTabID)const
{
	UYCNListDataObject_Collection* const* FoundTabCollectionPtr = RegistryOptionsTabList.FindByPredicate(
		[InSelectedTabID](UYCNListDataObject_Collection* AvailableTabCollection)
		{
			//遍历 RegistryOptionsTabList 如果遍历到的数据ID == 传进来的ID就返回这个数据
			return AvailableTabCollection->GetDataID() == InSelectedTabID;
		});
	if (!FoundTabCollectionPtr)return TArray<UYCNListDataObject_Base*>();

	//主标题
	UYCNListDataObject_Collection* FoundTabCollection = *FoundTabCollectionPtr;
	
	TArray<UYCNListDataObject_Base*>AllChildListItem;

	for (UYCNListDataObject_Base* ChildListData : FoundTabCollection->GetAllChildListData())
	{
		//遍历主标签的子数据列表
		if (!ChildListData)continue;	
		//再将遍历到的子数据列表添加到 AllChildListItem中
		AllChildListItem.Add(ChildListData);
		
		if (ChildListData->HasAnyChildListData())
		{
			//如果 ChildListData 也有子数据就将 ChildListData 的子数据添加到 AllChildListItem中
			FindChildListDataRecursively(ChildListData, AllChildListItem);
		}
	}
	return AllChildListItem;
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

		//音量
		{
			UYCNListDataObject_Collection* VolumeCategory = NewObject<UYCNListDataObject_Collection>();
			VolumeCategory->SetDataID(FName("VolumeCategory"));
			VolumeCategory->SetDataDisplayName(FText::FromString(TEXT("音量")));

			AudioTab->AddDataToChildDataList(VolumeCategory);

			//游戏主音量
			{
				UYCNListDataObject_Scalar* MainVolume = NewObject<UYCNListDataObject_Scalar>();
				MainVolume->SetDataID(FName("MainVolume"));
				MainVolume->SetDataDisplayName(FText::FromString(TEXT("主音量")));
				MainVolume->SetDescriptionRichText(FText::FromString(TEXT("调节游戏内所有声音的总音量。")));
				MainVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
				MainVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
				MainVolume->SetSliderStepSize(0.01f);
				MainVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
				MainVolume->SetNumberFormattingOptions(UYCNListDataObject_Scalar::NoDecimal());
				MainVolume->SetDefaultStringValue(LexToString(2.f));
				MainVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCachedMainVolume));
				MainVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCachedMainVolume));

				VolumeCategory->AddDataToChildDataList(MainVolume);
			}

			//音乐音量
			{
				UYCNListDataObject_Scalar* MusicVolume = NewObject<UYCNListDataObject_Scalar>();
				MusicVolume->SetDataID(FName("MusicVolume"));
				MusicVolume->SetDataDisplayName(FText::FromString(TEXT("背景音乐")));
				MusicVolume->SetDescriptionRichText(FText::FromString(TEXT("调节游戏内背景音乐与配乐的音量。")));
				MusicVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
				MusicVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
				MusicVolume->SetSliderStepSize(0.01f);
				MusicVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
				MusicVolume->SetNumberFormattingOptions(UYCNListDataObject_Scalar::NoDecimal());
				MusicVolume->SetDefaultStringValue(LexToString(2.f));
				MusicVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCachedMusicVolume));
				MusicVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCachedMusicVolume));

				VolumeCategory->AddDataToChildDataList(MusicVolume);
			}

			//音效音量
			{
				UYCNListDataObject_Scalar* SoundVolume = NewObject<UYCNListDataObject_Scalar>();
				SoundVolume->SetDataID(FName("SoundVolume"));
				SoundVolume->SetDataDisplayName(FText::FromString(TEXT("音效")));
				SoundVolume->SetDescriptionRichText(FText::FromString(TEXT("调节武器、战斗、环境互动与界面点击等音效的音量。")));
				SoundVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
				SoundVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
				SoundVolume->SetSliderStepSize(0.01f);
				SoundVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
				SoundVolume->SetNumberFormattingOptions(UYCNListDataObject_Scalar::NoDecimal());
				SoundVolume->SetDefaultStringValue(LexToString(2.f));
				SoundVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCachedSoundVolume));
				SoundVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCachedSoundVolume));

				VolumeCategory->AddDataToChildDataList(SoundVolume);
			}

		}

		//音效分类
		{
			UYCNListDataObject_Collection* SoundCategory = NewObject<UYCNListDataObject_Collection>();
			SoundCategory->SetDataID(FName("SoundCategory"));
			SoundCategory->SetDataDisplayName(FText::FromString(TEXT("音效")));

			AudioTab->AddDataToChildDataList(SoundCategory);

			//背景音效
			{
				UYCNListDataObject_StringBool* BackgroundAudio = NewObject<UYCNListDataObject_StringBool>();
				BackgroundAudio->SetDataID(FName("BackgroundAudio"));
				BackgroundAudio->SetDataDisplayName(FText::FromString(TEXT("背景音效")));
				BackgroundAudio->SetDescriptionRichText(FText::FromString(TEXT("控制是否播放场景与环境背景音。")));
				BackgroundAudio->SetFlaseDefaultValue();
				BackgroundAudio->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCachedBackgroundAudio));
				BackgroundAudio->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCachedBackgroundAudio));

				SoundCategory->AddDataToChildDataList(BackgroundAudio);
			}
			//HDR
			{
				UYCNListDataObject_StringBool* UseHDRAudioMode = NewObject<UYCNListDataObject_StringBool>();
				UseHDRAudioMode->SetDataID(FName("UseHDRAudioMode"));
				UseHDRAudioMode->SetDataDisplayName(FText::FromString(TEXT("HDR")));
				UseHDRAudioMode->SetDescriptionRichText(FText::FromString(TEXT("开启高动态范围渲染，呈现更深邃的暗部与更明亮的细节（需显示设备支持）。")));
				UseHDRAudioMode->SetFlaseDefaultValue();
				UseHDRAudioMode->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCachedUseHDRAudioMode));
				UseHDRAudioMode->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCachedUseHDRAudioMode));

				SoundCategory->AddDataToChildDataList(UseHDRAudioMode);
			}
		}
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

		UYCNListDataObject_StringEnum* CachedWindowMode = nullptr;
		//显示分类
		{
			UYCNListDataObject_Collection* DisplayCategory= NewObject<UYCNListDataObject_Collection>();
			DisplayCategory->SetDataID(FName("DisplayCategory"));
			DisplayCategory->SetDataDisplayName(FText::FromString(TEXT("显示")));

			VideoTab->AddDataToChildDataList(DisplayCategory);
			FOptionDataEditConditionDescriptor PackagedBuildOnlyCondition;
			PackagedBuildOnlyCondition.SetEditConditionFunc(
				[]()->bool
				{
					const bool bIsInEditor = GIsEditor || GIsPlayInEditorWorld;
					//如果当前状态在引擎里就返回false
					return !bIsInEditor;
				});
			PackagedBuildOnlyCondition.SetDisableRichReason(TEXT("<Disable>这个选项只能在打包构建后修改</>"));

			//窗口模式
			{
				UYCNListDataObject_StringEnum* WindowMode = NewObject<UYCNListDataObject_StringEnum>();
				WindowMode->SetDataID(FName("WindowMode"));
				WindowMode->SetDataDisplayName(FText::FromString(TEXT("窗口模式")));
				WindowMode->SetDescriptionRichText(FText::FromString(TEXT("选择游戏画面的呈现方式，不同模式会影响输入延迟、切屏便利性及画面性能。")));
				WindowMode->AddEnumOption(EWindowMode::Fullscreen, FText::FromString(TEXT("独占全屏")));
				WindowMode->AddEnumOption(EWindowMode::WindowedFullscreen, FText::FromString(TEXT("无边框窗口")));
				WindowMode->AddEnumOption(EWindowMode::Windowed, FText::FromString(TEXT("窗口化")));
				WindowMode->SetDefaultValueFromEnumOption(EWindowMode::WindowedFullscreen);
				WindowMode->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetFullscreenMode));
				WindowMode->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetFullscreenMode));
				WindowMode->AddEditCondition(PackagedBuildOnlyCondition);
				WindowMode->SetbApplyImmediately(true);
				CachedWindowMode = WindowMode;
				
				DisplayCategory->AddDataToChildDataList(WindowMode);
			}

			//分辨率
			{
				UYCNListDataObject_Resolution* ScreenResolution = NewObject<UYCNListDataObject_Resolution>();
				ScreenResolution->SetDataID(FName("ScreenResolution"));
				ScreenResolution->SetDataDisplayName(FText::FromString(TEXT("屏幕分辨率")));
				ScreenResolution->SetDescriptionRichText(FText::FromString(TEXT("调整屏幕像素尺寸。分辨率越高画面越清晰，但对显卡性能要求更高。")));
				ScreenResolution->InitResolutionValue();
				ScreenResolution->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetScreenResolution));
				ScreenResolution->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetScreenResolution));
				ScreenResolution->SetbApplyImmediately(true);
				ScreenResolution->AddEditCondition(PackagedBuildOnlyCondition);

				FOptionDataEditConditionDescriptor WindowModeEditCondition;
				WindowModeEditCondition.SetEditConditionFunc(
					[CachedWindowMode]()->bool
					{
						if (CachedWindowMode->GetCurrentEnum<EWindowMode::Type>() == EWindowMode::WindowedFullscreen)return false;
						return true;
					});
				WindowModeEditCondition.SetDisableRichReason(TEXT("\n\n<Disable>当窗口模式为无边框窗口时则无法更改屏幕分辨率</>"));
				WindowModeEditCondition.SetDisableValue(ScreenResolution->GetMaxResolution());

				ScreenResolution->AddEditCondition(WindowModeEditCondition);
				ScreenResolution->AddEditDependencyData(CachedWindowMode);
				
				DisplayCategory->AddDataToChildDataList(ScreenResolution);
			}
		}
		//图像分类
		{
			UYCNListDataObject_Collection* GraphicsCategory = NewObject<UYCNListDataObject_Collection>();
			GraphicsCategory->SetDataID(FName("GraphicsCategory"));
			GraphicsCategory->SetDataDisplayName(FText::FromString(TEXT("图像")));

			VideoTab->AddDataToChildDataList(GraphicsCategory);
			//亮度
			{
				UYCNListDataObject_Scalar* DiaplayGamma = NewObject<UYCNListDataObject_Scalar>();
				DiaplayGamma->SetDataID(FName("DiaplayGamma"));
				DiaplayGamma->SetDataDisplayName(FText::FromString(TEXT("亮度")));
				DiaplayGamma->SetDescriptionRichText(FText::FromString(TEXT("调节游戏画面的整体明暗程度。如果画面过暗，可以适当调高此数值。")));
				DiaplayGamma->SetDisplayValueRange(TRange<float>(0.f, 1.f));
				DiaplayGamma->SetOutputValueRange(TRange<float>(1.1f, 3.3f));
				DiaplayGamma->SetDisplayNumericType(ECommonNumericType::Percentage);
				DiaplayGamma->SetNumberFormattingOptions(UYCNListDataObject_Scalar::NoDecimal());
				DiaplayGamma->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentDiaplayGamma));
				DiaplayGamma->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentDiaplayGamma));
				DiaplayGamma->SetDefaultStringValue(LexToString(2.2f));
				DiaplayGamma->SetbApplyImmediately(true);
				GraphicsCategory->AddDataToChildDataList(DiaplayGamma);
			}

			UYCNListDataObject_StringNumber* CachedOverallQuality = nullptr;
			//整体画质
			{
				UYCNListDataObject_StringNumber* OverallQuality = NewObject<UYCNListDataObject_StringNumber>();
				OverallQuality->SetDataID(FName("OverallQuality"));
				OverallQuality->SetDataDisplayName(FText::FromString(TEXT("画面质量")));
				OverallQuality->SetDescriptionRichText(FText::FromString(TEXT("调节游戏整体的图形渲染精度。降低画质可提升运行流畅度，提高画质可获得更精细的视觉效果。")));
				OverallQuality->AddNumberOptions<int32>(0, FText::FromString(TEXT("低")));
				OverallQuality->AddNumberOptions<int32>(1, FText::FromString(TEXT("中")));
				OverallQuality->AddNumberOptions<int32>(2, FText::FromString(TEXT("高")));
				OverallQuality->AddNumberOptions<int32>(3, FText::FromString(TEXT("极高")));
				OverallQuality->AddNumberOptions<int32>(4, FText::FromString(TEXT("影视级")));
				OverallQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallScalabilityLevel));
				OverallQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallScalabilityLevel));
				OverallQuality->SetDefaultStringValue(LexToString(1));
				OverallQuality->SetbApplyImmediately(true);
				CachedOverallQuality = OverallQuality;
				GraphicsCategory->AddDataToChildDataList(OverallQuality);
			}

			//分辨率缩放
			{
				UYCNListDataObject_StringNumber* ResolutionScale = NewObject<UYCNListDataObject_StringNumber>();
				ResolutionScale->SetDataID(FName("ResolutionScale"));
				ResolutionScale->SetDataDisplayName(FText::FromString(TEXT("分辨率大小")));
				ResolutionScale->SetDescriptionRichText(FText::FromString(TEXT("决定画面的像素点数量。分辨率越高，画面边缘与细节越清晰，但会显著增加显卡性能开销。")));
				ResolutionScale->AddNumberOptions<float>(50.f, FText::FromString(TEXT("低")));
				ResolutionScale->AddNumberOptions<float>(71.f, FText::FromString(TEXT("中")));
				ResolutionScale->AddNumberOptions<float>(87.f, FText::FromString(TEXT("高")));
				ResolutionScale->AddNumberOptions<float>(100.f, FText::FromString(TEXT("极高")));
				ResolutionScale->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentResolutionScalePercent));
				ResolutionScale->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetResolutionScaleValueEx));
				ResolutionScale->SetDefaultStringValue(LexToString(71.f));
				ResolutionScale->SetbApplyImmediately(true);

				ResolutionScale->AddEditDependencyData(CachedOverallQuality);
				CachedOverallQuality->AddEditDependencyData(ResolutionScale);

				GraphicsCategory->AddDataToChildDataList(ResolutionScale);
			}
			//可视距离
			{
				UYCNListDataObject_StringNumber* ViewDistance = NewObject<UYCNListDataObject_StringNumber>();
				ViewDistance->SetDataID(FName("ViewDistance"));
				ViewDistance->SetDataDisplayName(FText::FromString(TEXT("可视距离")));
				ViewDistance->SetDescriptionRichText(FText::FromString(TEXT("控制远处物体、建筑和地形的渲染范围。调高此项可减少远景突然出现的现象，但会消耗较多CPU和GPU资源。")));
				ViewDistance->AddNumberOptions<int32>(0, FText::FromString(TEXT("近")));
				ViewDistance->AddNumberOptions<int32>(1, FText::FromString(TEXT("中")));
				ViewDistance->AddNumberOptions<int32>(2, FText::FromString(TEXT("远")));
				ViewDistance->AddNumberOptions<int32>(3, FText::FromString(TEXT("极远")));
				ViewDistance->AddNumberOptions<int32>(4, FText::FromString(TEXT("影视级")));
				ViewDistance->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetViewDistanceQuality));
				ViewDistance->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetViewDistanceQuality));
				ViewDistance->SetDefaultStringValue(LexToString(1));
				ViewDistance->SetbApplyImmediately(true);

				ViewDistance->AddEditDependencyData(CachedOverallQuality);
				CachedOverallQuality->AddEditDependencyData(ViewDistance);

				GraphicsCategory->AddDataToChildDataList(ViewDistance);
			}
			//全局光照
			{
				UYCNListDataObject_StringNumber* GlobalIllumination = NewObject<UYCNListDataObject_StringNumber>();
				GlobalIllumination->SetDataID(FName("GlobalIllumination"));
				GlobalIllumination->SetDataDisplayName(FText::FromString(TEXT("全局光照"))); 
				GlobalIllumination->SetDescriptionRichText(FText::FromString(TEXT("控制光线在场景表面的反射和漫反射。开启或调高此项能让阴影更自然、光影更柔和，但会带来较大的性能开销。")));
				GlobalIllumination->AddNumberOptions<int32>(0, FText::FromString(TEXT("低")));
				GlobalIllumination->AddNumberOptions<int32>(1, FText::FromString(TEXT("中")));
				GlobalIllumination->AddNumberOptions<int32>(2, FText::FromString(TEXT("高")));
				GlobalIllumination->AddNumberOptions<int32>(3, FText::FromString(TEXT("极高")));
				GlobalIllumination->AddNumberOptions<int32>(4, FText::FromString(TEXT("影视级")));
				GlobalIllumination->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetGlobalIlluminationQuality));
				GlobalIllumination->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetGlobalIlluminationQuality));
				GlobalIllumination->SetDefaultStringValue(LexToString(1));
				GlobalIllumination->SetbApplyImmediately(true);

				GlobalIllumination->AddEditDependencyData(CachedOverallQuality);
				CachedOverallQuality->AddEditDependencyData(GlobalIllumination);

				GraphicsCategory->AddDataToChildDataList(GlobalIllumination);
			}
			//阴影
			{
				UYCNListDataObject_StringNumber* ShadowQuality = NewObject<UYCNListDataObject_StringNumber>();
				ShadowQuality->SetDataID(FName("ShadowQuality"));
				ShadowQuality->SetDataDisplayName(FText::FromString(TEXT("阴影质量")));
				ShadowQuality->SetDescriptionRichText(FText::FromString(TEXT("控制光线在场景表面的反射和漫反射。开启或调高此项能让阴影更自然、光影更柔和，但会带来较大的性能开销。")));
				ShadowQuality->AddNumberOptions<int32>(0, FText::FromString(TEXT("低")));
				ShadowQuality->AddNumberOptions<int32>(1, FText::FromString(TEXT("中")));
				ShadowQuality->AddNumberOptions<int32>(2, FText::FromString(TEXT("高")));
				ShadowQuality->AddNumberOptions<int32>(3, FText::FromString(TEXT("极高")));
				ShadowQuality->AddNumberOptions<int32>(4, FText::FromString(TEXT("影视级")));
				ShadowQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetShadowQuality));
				ShadowQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetShadowQuality));
				ShadowQuality->SetDefaultStringValue(LexToString(1));
				ShadowQuality->SetbApplyImmediately(true);

				ShadowQuality->AddEditDependencyData(CachedOverallQuality);
				CachedOverallQuality->AddEditDependencyData(ShadowQuality);

				GraphicsCategory->AddDataToChildDataList(ShadowQuality);
			}

			//抗锯齿质量
			{
				UYCNListDataObject_StringNumber* AntiAliasingQuality = NewObject<UYCNListDataObject_StringNumber>();
				AntiAliasingQuality->SetDataID(FName("AntiAliasingQuality"));
				AntiAliasingQuality->SetDataDisplayName(FText::FromString(TEXT("抗锯齿质量")));
				AntiAliasingQuality->SetDescriptionRichText(FText::FromString(TEXT("消除物体边缘的“锯齿状”毛边，让线条和平滑过渡更自然。")));
				AntiAliasingQuality->AddNumberOptions<int32>(0, FText::FromString(TEXT("低")));
				AntiAliasingQuality->AddNumberOptions<int32>(1, FText::FromString(TEXT("中")));
				AntiAliasingQuality->AddNumberOptions<int32>(2, FText::FromString(TEXT("高")));
				AntiAliasingQuality->AddNumberOptions<int32>(3, FText::FromString(TEXT("极高")));
				AntiAliasingQuality->AddNumberOptions<int32>(4, FText::FromString(TEXT("影视级")));
				AntiAliasingQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetAntiAliasingQuality));
				AntiAliasingQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetAntiAliasingQuality));
				AntiAliasingQuality->SetDefaultStringValue(LexToString(1));
				AntiAliasingQuality->SetbApplyImmediately(true);

				AntiAliasingQuality->AddEditDependencyData(CachedOverallQuality);
				CachedOverallQuality->AddEditDependencyData(AntiAliasingQuality);

				GraphicsCategory->AddDataToChildDataList(AntiAliasingQuality);
			}
			//后期处理
			{
				UYCNListDataObject_StringNumber* PostProcessing = NewObject<UYCNListDataObject_StringNumber>();
				PostProcessing->SetDataID(FName("PostProcessing"));
				PostProcessing->SetDataDisplayName(FText::FromString(TEXT("后期处理")));
				PostProcessing->SetDescriptionRichText(FText::FromString(TEXT("控制画面整体的氛围渲染与视觉特效（如泛光、景深、环境光遮蔽等），增强画面的电影感与真实感。")));
				PostProcessing->AddNumberOptions<int32>(0, FText::FromString(TEXT("低")));
				PostProcessing->AddNumberOptions<int32>(1, FText::FromString(TEXT("中")));
				PostProcessing->AddNumberOptions<int32>(2, FText::FromString(TEXT("高")));
				PostProcessing->AddNumberOptions<int32>(3, FText::FromString(TEXT("极高")));
				PostProcessing->AddNumberOptions<int32>(4, FText::FromString(TEXT("影视级")));
				PostProcessing->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetPostProcessingQuality));
				PostProcessing->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetPostProcessingQuality));
				PostProcessing->SetDefaultStringValue(LexToString(1));
				PostProcessing->SetbApplyImmediately(true);

				PostProcessing->AddEditDependencyData(CachedOverallQuality);
				CachedOverallQuality->AddEditDependencyData(PostProcessing);

				GraphicsCategory->AddDataToChildDataList(PostProcessing);
			}
			//反射质量
			{
				UYCNListDataObject_StringNumber* Reflections = NewObject<UYCNListDataObject_StringNumber>();
				Reflections->SetDataID(FName("Reflections"));
				Reflections->SetDataDisplayName(FText::FromString(TEXT("反射质量")));
				Reflections->SetDescriptionRichText(FText::FromString(TEXT("决定水面、镜面及光滑表面的反射清晰度与准确度。调高此项能带来更逼真的反射效果。")));
				Reflections->AddNumberOptions<int32>(0, FText::FromString(TEXT("低")));
				Reflections->AddNumberOptions<int32>(1, FText::FromString(TEXT("中")));
				Reflections->AddNumberOptions<int32>(2, FText::FromString(TEXT("高")));
				Reflections->AddNumberOptions<int32>(3, FText::FromString(TEXT("极高")));
				Reflections->AddNumberOptions<int32>(4, FText::FromString(TEXT("影视级")));
				Reflections->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetReflectionQuality));
				Reflections->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetReflectionQuality));
				Reflections->SetDefaultStringValue(LexToString(1));
				Reflections->SetbApplyImmediately(true);

				Reflections->AddEditDependencyData(CachedOverallQuality);
				CachedOverallQuality->AddEditDependencyData(Reflections);

				GraphicsCategory->AddDataToChildDataList(Reflections);
			}
			//贴图质量
			{
				UYCNListDataObject_StringNumber* Textures = NewObject<UYCNListDataObject_StringNumber>();
				Textures->SetDataID(FName("Textures"));
				Textures->SetDataDisplayName(FText::FromString(TEXT("贴图质量")));
				Textures->SetDescriptionRichText(FText::FromString(TEXT("控制物体纹理的清晰度。主要消耗显存，显存足够时对帧率影响较小。")));
				Textures->AddNumberOptions<int32>(0, FText::FromString(TEXT("低")));
				Textures->AddNumberOptions<int32>(1, FText::FromString(TEXT("中")));
				Textures->AddNumberOptions<int32>(2, FText::FromString(TEXT("高")));
				Textures->AddNumberOptions<int32>(3, FText::FromString(TEXT("极高")));
				Textures->AddNumberOptions<int32>(4, FText::FromString(TEXT("影视级")));
				Textures->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetTextureQuality));
				Textures->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetTextureQuality));
				Textures->SetDefaultStringValue(LexToString(1));
				Textures->SetbApplyImmediately(true);

				Textures->AddEditDependencyData(CachedOverallQuality);
				CachedOverallQuality->AddEditDependencyData(Textures);

				GraphicsCategory->AddDataToChildDataList(Textures);
			}
			//特效质量
			{
				UYCNListDataObject_StringNumber* Effects = NewObject<UYCNListDataObject_StringNumber>();
				Effects->SetDataID(FName("Effects"));
				Effects->SetDataDisplayName(FText::FromString(TEXT("特效质量")));
				Effects->SetDescriptionRichText(FText::FromString(TEXT("决定爆炸、火焰、烟雾等粒子特效的复杂程度与数量。在激烈战斗中降低此项有助于保持帧率稳定。")));
				Effects->AddNumberOptions<int32>(0, FText::FromString(TEXT("低")));
				Effects->AddNumberOptions<int32>(1, FText::FromString(TEXT("中")));
				Effects->AddNumberOptions<int32>(2, FText::FromString(TEXT("高")));
				Effects->AddNumberOptions<int32>(3, FText::FromString(TEXT("极高")));
				Effects->AddNumberOptions<int32>(4, FText::FromString(TEXT("影视级")));
				Effects->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetVisualEffectQuality));
				Effects->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetVisualEffectQuality));
				Effects->SetDefaultStringValue(LexToString(1));
				Effects->SetbApplyImmediately(true);

				Effects->AddEditDependencyData(CachedOverallQuality);
				CachedOverallQuality->AddEditDependencyData(Effects);

				GraphicsCategory->AddDataToChildDataList(Effects);
			}
			//植物质量
			{
				UYCNListDataObject_StringNumber* Foliage = NewObject<UYCNListDataObject_StringNumber>();
				Foliage->SetDataID(FName("Foliage"));
				Foliage->SetDataDisplayName(FText::FromString(TEXT("植物质量")));
				Foliage->SetDescriptionRichText(FText::FromString(TEXT("控制草丛、树木的密度、渲染范围及风吹动时的动态表现。调高此项可使野外场景更茂密真实。")));
				Foliage->AddNumberOptions<int32>(0, FText::FromString(TEXT("低")));
				Foliage->AddNumberOptions<int32>(1, FText::FromString(TEXT("中")));
				Foliage->AddNumberOptions<int32>(2, FText::FromString(TEXT("高")));
				Foliage->AddNumberOptions<int32>(3, FText::FromString(TEXT("极高")));
				Foliage->AddNumberOptions<int32>(4, FText::FromString(TEXT("影视级")));
				Foliage->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetFoliageQuality));
				Foliage->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetFoliageQuality));
				Foliage->SetDefaultStringValue(LexToString(1));
				Foliage->SetbApplyImmediately(true);

				Foliage->AddEditDependencyData(CachedOverallQuality);
				CachedOverallQuality->AddEditDependencyData(Foliage);

				GraphicsCategory->AddDataToChildDataList(Foliage);
			}
			//着色质量
			{
				UYCNListDataObject_StringNumber* Shading = NewObject<UYCNListDataObject_StringNumber>();
				Shading->SetDataID(FName("Shading"));
				Shading->SetDataDisplayName(FText::FromString(TEXT("着色质量")));
				Shading->SetDescriptionRichText(FText::FromString(TEXT("决定材质表面的光照计算与表面细节表现。高设置下能呈现更好的材质质感，但会增加显卡渲染负担。")));
				Shading->AddNumberOptions<int32>(0, FText::FromString(TEXT("低")));
				Shading->AddNumberOptions<int32>(1, FText::FromString(TEXT("中")));
				Shading->AddNumberOptions<int32>(2, FText::FromString(TEXT("高")));
				Shading->AddNumberOptions<int32>(3, FText::FromString(TEXT("极高")));
				Shading->AddNumberOptions<int32>(4, FText::FromString(TEXT("影视级")));
				Shading->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetShadingQuality));
				Shading->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetShadingQuality));
				Shading->SetDefaultStringValue(LexToString(1));
				Shading->SetbApplyImmediately(true);

				Shading->AddEditDependencyData(CachedOverallQuality);
				CachedOverallQuality->AddEditDependencyData(Shading);

				GraphicsCategory->AddDataToChildDataList(Shading);
			}
		}
		//高级图像分类
		{
			UYCNListDataObject_Collection* AdvancedGraphicsCategory = NewObject<UYCNListDataObject_Collection>();
			AdvancedGraphicsCategory->SetDataID(FName("AdvancedGraphicsCategory"));
			AdvancedGraphicsCategory->SetDataDisplayName(FText::FromString(TEXT("高级图像")));

			VideoTab->AddDataToChildDataList(AdvancedGraphicsCategory);

			//垂直同步
			{
				UYCNListDataObject_StringBool* VerticalSync = NewObject<UYCNListDataObject_StringBool>();
				VerticalSync->SetDataID(FName("VerticalSync"));
				VerticalSync->SetDataDisplayName(FText::FromString(TEXT("垂直同步")));
				VerticalSync->SetDescriptionRichText(FText::FromString(TEXT("将游戏帧率与显示器刷新率同步，以消除画面撕裂现象。")));
				VerticalSync->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(IsVSyncEnabled));
				VerticalSync->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetVSyncEnabled));
				VerticalSync->SetFlaseDefaultValue();
				VerticalSync->SetbApplyImmediately(true);

				FOptionDataEditConditionDescriptor FullscreenOnly;//仅限全屏时

				FullscreenOnly.SetEditConditionFunc(
					[CachedWindowMode]()->bool
					{
						return CachedWindowMode->GetCurrentEnum<EWindowMode::Type>() == EWindowMode::Fullscreen;
					});
				FullscreenOnly.SetDisableRichReason(TEXT("<Disabled>此功能仅在窗口模式为独占全屏时可更改。</>"));
				FullscreenOnly.SetDisableValue(TEXT("false"));
				VerticalSync->AddEditCondition(FullscreenOnly);

				AdvancedGraphicsCategory->AddDataToChildDataList(VerticalSync);
			}
			//帧率
			{
				UYCNListDataObject_String* FrameRate = NewObject<UYCNListDataObject_String>();
				FrameRate->SetDataID(FName("FrameRate"));
				FrameRate->SetDataDisplayName(FText::FromString(TEXT("帧率")));
				FrameRate->SetDescriptionRichText(FText::FromString(TEXT("限制游戏运行的最大帧率，以平衡画面流畅度与硬件功耗。")));
				FrameRate->AddDynamicOption(LexToString(30.f), FText::FromString(TEXT("30 FPS")));
				FrameRate->AddDynamicOption(LexToString(45.f), FText::FromString(TEXT("45 FPS")));
				FrameRate->AddDynamicOption(LexToString(60.f), FText::FromString(TEXT("60 FPS")));
				FrameRate->AddDynamicOption(LexToString(90.f), FText::FromString(TEXT("90 FPS")));
				FrameRate->AddDynamicOption(LexToString(120.f), FText::FromString(TEXT("120 FPS")));
				FrameRate->AddDynamicOption(LexToString(0.f), FText::FromString(TEXT("无限制")));
				FrameRate->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetFrameRateLimit));
				FrameRate->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetFrameRateLimit));
				FrameRate->SetDefaultStringValue(LexToString(0.f));
				FrameRate->SetbApplyImmediately(true);

				AdvancedGraphicsCategory->AddDataToChildDataList(FrameRate);
			}
		}
	}
}

void UYCNOptionsDataRegistry::InitControlCollectionTab(ULocalPlayer* InOwningLocalPlayer)
{
	UYCNListDataObject_Collection* ControlTab = NewObject<UYCNListDataObject_Collection>();
	ControlTab->SetDataID(FName("Control"));
	ControlTab->SetDataDisplayName(FText::FromString(TEXT("控制")));

	RegistryOptionsTabList.Add(ControlTab);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = InOwningLocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!Subsystem)return;
	UEnhancedInputUserSettings* UserSetting = Subsystem->GetUserSettings();
	if (!UserSetting)return;

	//键盘/鼠标
	{
		UYCNListDataObject_Collection* KeyboardMouseCategory = NewObject<UYCNListDataObject_Collection>();
		KeyboardMouseCategory->SetDataID(FName("KeyboardMouseCategory"));
		KeyboardMouseCategory->SetDataDisplayName(FText::FromString(TEXT("键盘/鼠标")));

		ControlTab->AddDataToChildDataList(KeyboardMouseCategory);

		//键盘/鼠标输入
		{
			FPlayerMappableKeyQueryOptions KeyboardMouseOnly;
			KeyboardMouseOnly.KeyToMatch = EKeys::S;
			KeyboardMouseOnly.bMatchBasicKeyTypes = true;

			for (const TPair<FGameplayTag, UEnhancedPlayerMappableKeyProfile*>& ProfilePair : UserSetting->GetAllSavedKeyProfiles())
			{
				UEnhancedPlayerMappableKeyProfile* MappableKeyProfile = ProfilePair.Value;
				if (!MappableKeyProfile)return;
				for (const TPair<FName, FKeyMappingRow>& MappingRowPair : MappableKeyProfile->GetPlayerMappingRows())
				{
					for (const FPlayerKeyMapping& KeyMapping : MappingRowPair.Value.Mappings)
					{
						if (MappableKeyProfile->DoesMappingPassQueryOptions(KeyMapping, KeyboardMouseOnly))
						{
							UYCNListDataObject_KeyRemap* KeyRemapDataObject = NewObject<UYCNListDataObject_KeyRemap>();
							KeyRemapDataObject->SetDataID(KeyMapping.GetMappingName());
							KeyRemapDataObject->SetDataDisplayName(KeyMapping.GetDisplayName());
							KeyRemapDataObject->InitKeyRemapData(UserSetting, MappableKeyProfile, ECommonInputType::MouseAndKeyboard, KeyMapping);

							KeyboardMouseCategory->AddDataToChildDataList(KeyRemapDataObject);
						}
					}
				}
			}
		}
	}
}

void UYCNOptionsDataRegistry::FindChildListDataRecursively(UYCNListDataObject_Base* InParentData, TArray<UYCNListDataObject_Base*>& OutFoundChaildListData)const
{
	if (!InParentData || !InParentData->HasAnyChildListData())return;

	for (UYCNListDataObject_Base* SubChildListData : InParentData->GetAllChildListData())
	{
		if (!SubChildListData)continue;

		OutFoundChaildListData.Add(SubChildListData);

		if (SubChildListData->HasAnyChildListData())
		{
			FindChildListDataRecursively(SubChildListData, OutFoundChaildListData);
		}
	}
}
