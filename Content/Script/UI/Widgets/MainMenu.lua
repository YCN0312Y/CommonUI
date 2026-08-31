--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

local YCNFunctionLibrary = UE.UYCNFunctionLibrary
---@type WBP_CAW_MainMenu_C
local M = UnLua.Class()

function M:OnInitialized()

    if self.Button_Quit then
        self.Button_Quit.OnButtonBaseClicked:Add(self, M.OnClickedButton_Quit)
    end
    if self.Button_Stroy then
        self.Button_Stroy.OnButtonBaseClicked:Add(self, M.OnClickedButton_Stroy)
    end
        if self.Button_Options then
        self.Button_Options.OnButtonBaseClicked:Add(self, M.OnClickedButton_Option)
    end
end

--function M:PreConstruct(IsDesignTime)
--end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

--退出游戏回调函数
function M:OnClickedButton_Quit(Button)

    if UE.UYCNAsyncAction_PushConfirmWindow then
        local AsyncAction = UE.UYCNAsyncAction_PushConfirmWindow.PushConfirmWindow(self, UE.EConfirmWindowType.YesNo, "退出游戏", "确定退出游戏？")
        if AsyncAction then
            AsyncAction.OnButtonClicked:Add(self, M.OnConfirmWindowButtonClicked)

            AsyncAction:Activate()
        end
    end

end

function M:OnConfirmWindowButtonClicked(ButtonType)
    if ButtonType == UE.EConfirmWindowButtonType.Confirm then
        UE.UKismetSystemLibrary.QuitGame(self, nil, UE.EQuitPreference.Quit, false)
    end
end

--故事回调函数
function M:OnClickedButton_Stroy(Button)

    local CachedOwningPC = self:GetCachedOwningPC()
    local StoryWidgetTag = self.WidgetStackTags:Find("Story")

    if UE.UYCNAsyncAction_PushSoftWidget and CachedOwningPC and YCNFunctionLibrary and StoryWidgetTag then
        local StoryWidgetClass = YCNFunctionLibrary.GetSoftWidgetClassByTag(StoryWidgetTag)
        if StoryWidgetClass then
            local AsyncAction = UE.UYCNAsyncAction_PushSoftWidget.PushSoftWidget(self, CachedOwningPC, StoryWidgetClass, self.WidgetTag, true)
            if AsyncAction then
                AsyncAction:Activate()
            end
        end
    end
end

--选项回调函数
function M:OnClickedButton_Option(Button)

    local CachedOwningPC = self:GetCachedOwningPC()
    local OptionWidgetTag = self.WidgetStackTags:Find("Option")

    if UE.UYCNAsyncAction_PushSoftWidget and CachedOwningPC and YCNFunctionLibrary and OptionWidgetTag then
        local OptionWidgetClass = YCNFunctionLibrary.GetSoftWidgetClassByTag(OptionWidgetTag)
        if OptionWidgetClass then
            local AsyncAction = UE.UYCNAsyncAction_PushSoftWidget.PushSoftWidget(self, CachedOwningPC, OptionWidgetClass, self.WidgetTag, true)
            if AsyncAction then
                AsyncAction:Activate()
            end
        end
    end
end

return M
