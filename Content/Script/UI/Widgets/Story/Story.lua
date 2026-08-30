--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

local PushConfirmWindowAction = UE.UYCNAsyncAction_PushConfirmWindow
---@type WBP_CAW_Story_C
local M = UnLua.Class()

function M:OnInitialized()
    if self.Button_NewGame then
        self.Button_NewGame.OnButtonBaseClicked:Add(self, M.OnClickButton_NewGame)
    end
end

--function M:PreConstruct(IsDesignTime)
--end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

function M:BP_OnActivated()
    if self.Button_ContinueGame and self.Button_MoreGame then
        self.Button_ContinueGame:SetIsInteractionEnabled(false)
        self.Button_ContinueGame:SetIsFocusable(false)
        self.Button_MoreGame:SetIsInteractionEnabled(false)
        self.Button_MoreGame:SetIsFocusable(false)
    end
end

function M:OnClickButton_NewGame(Button)
    if PushConfirmWindowAction then
        AsyncAction = PushConfirmWindowAction.PushConfirmWindow(self, UE.EConfirmWindowType.OK, "创建游戏", "正在创建游戏中...")
        if AsyncAction then
            AsyncAction:Activate()
        end
    end
end

return M
