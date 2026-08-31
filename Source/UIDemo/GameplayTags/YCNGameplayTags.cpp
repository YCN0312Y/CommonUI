// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDemo/GameplayTags/YCNGameplayTags.h"

namespace YCNGameplayTags
{
	//Widget Stack
	UE_DEFINE_GAMEPLAY_TAG(YCN_WidgetStack_Modal, "YCN.WidgetStack.Modal");
	UE_DEFINE_GAMEPLAY_TAG(YCN_WidgetStack_GameMenu, "YCN.WidgetStack.GameMenu");
	UE_DEFINE_GAMEPLAY_TAG(YCN_WidgetStack_GameHUD, "YCN.WidgetStack.GameHUD");
	UE_DEFINE_GAMEPLAY_TAG(YCN_WidgetStack_Frontend, "YCN.WidgetStack.Frontend");

	//Widget
	UE_DEFINE_GAMEPLAY_TAG(YCN_Widget_PressAntKey, "YCN.Widget.PressAntKey");
	UE_DEFINE_GAMEPLAY_TAG(YCN_Widget_MainMenu, "YCN.Widget.MainMenu");
	UE_DEFINE_GAMEPLAY_TAG(YCN_Widget_Confirm, "YCN.Widget.Confirm");
	UE_DEFINE_GAMEPLAY_TAG(YCN_Widget_Option, "YCN.Widget.Option");
}